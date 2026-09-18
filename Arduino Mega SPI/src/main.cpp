#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile char receivedData[64];
volatile uint8_t index = 0;
volatile bool messageReady = false;

//MISO D50 PB3
//MOSI D51 PB2
//SCK D52 PB1
//SS D53 PB0

/*Pin change interrupt at PB0 so, when SS is pulled low, the interrupt will trigger and the data will be read from the SPI bus.
PB0 is connected to PCINT0, Pin Change Interrupt 0
PCINT0 is enabled by PCICR--PCIE0(0)
PCMSK0--PCINT0(0)
SREG--I bit(7) = 1; Global Interrupt has to be enabled*/

void setup() {
  Serial.begin(115200);

  cli();

  DDRB &= ~(1<<PB2);
  PORTB &= ~(1<<PB2); //MOSI pin configured as input with pull up resistor off

  DDRB &= ~(1<<PB1);
  PORTB &= ~(1<<PB1); //SCK pin configured as input with pull up resistor off

  DDRB &= ~(1<<PB0);
  PORTB |= (1<<PB0); //SS pin configured as input with pull up resistor on

  SPCR |= (1<<SPE) | (1<<SPIE);
  SPCR &= ~((1<<MSTR) | (1<<DORD) | (1<<CPOL) | (1<<CPHA)); 

  PCICR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT0);

  sei();

  Serial.print("SPI Slave on Mega2560 configured.");
}

ISR(SPI_STC_vect) {
  char data = SPDR;

  if (!(PINB & (1<<PB0))){
    if (index < sizeof(receivedData) - 1){
      receivedData[index++] = data;
    }
  }
}

ISR(PCINT0_vect){
  if ((PINB & (1<<PB0))){
    if (index>0){
      receivedData[index] = '\0';
      messageReady = true;
      index = 0;
    }
  }
}

void loop() {
  if(messageReady){
    messageReady = false;
    Serial.print("Received data: ");
    Serial.println((char*)receivedData);
  }
}