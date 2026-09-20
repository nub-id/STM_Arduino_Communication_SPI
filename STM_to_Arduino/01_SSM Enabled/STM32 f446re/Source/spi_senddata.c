/*
 * spi_senddata.c
 *
 *  Created on: Sep 17, 2026
 *      Author: User
 */

#include <stdint.h>
#include <string.h>

#include "STM32_f446re.h"
#include "STM32f446re_GPIO.h"
#include "STM32f446re_SPI_driver.h"

//SPI2 SCK PB10
//SPI2 NSS PB9
//SPI2 MISO PB14
//SPI2 MOSI PB15

void SPI2_GPIO_Init(void){
	GPIO_Handle_t SPI2_pins;

	SPI2_pins.pGPIOxAddr = GPIOB;
	SPI2_pins.GPIO_Config.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPI2_pins.GPIO_Config.GPIO_PinAltFuncMode = 5;
	SPI2_pins.GPIO_Config.GPIO_PUPDControl = GPIO_NO_PUPD;
	SPI2_pins.GPIO_Config.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPI2_pins.GPIO_Config.GPIO_PinSpeed = GPIO_SPEED_FAST;


	SPI2_pins.GPIO_Config.GPIO_Pin_Number = GPIO_PIN_NO_10;
	GPIO_Init(&SPI2_pins);

	SPI2_pins.GPIO_Config.GPIO_Pin_Number = GPIO_PIN_NO_14;
	GPIO_Init(&SPI2_pins);

	SPI2_pins.GPIO_Config.GPIO_Pin_Number = GPIO_PIN_NO_15;
	GPIO_Init(&SPI2_pins);

	GPIOB->BSRR = (1U << 9);

	SPI2_pins.GPIO_Config.GPIO_Pin_Number = GPIO_PIN_NO_9;
	SPI2_pins.GPIO_Config.GPIO_PinMode = GPIO_MODE_OUTPUT;
	GPIO_Init(&SPI2_pins);


}

void SPI2_Init(void){
	SPI_Handle_t SPI2_h;

	SPI2_h.pSPIx = SPI2;
	SPI2_h.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2_h.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2_h.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2_h.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2_h.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2_h.SPIConfig.SPI_Speed = SPI_SCLK_SPEED_DIV256;
	SPI2_h.SPIConfig.SPI_SSM = SPI_SSM_EN;

	SPI_Init(&SPI2_h);
}

void delay(uint8_t n)
{
	for(uint32_t i = 0; i<n*500000; i++);
}

int main(){
	SPI2_GPIO_Init();
	SPI2_Init();

	SPI_SSIConfig(SPI2, ENABLE);
	SPI_PeripheralControl(SPI2, ENABLE);

	char user_data[] = "Hello World";

	GPIO_WriteToPin(GPIOB, GPIO_PIN_NO_9, GPIO_PIN_RESET);
	SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

	delay(1);

	GPIO_WriteToPin(GPIOB, GPIO_PIN_NO_9, GPIO_PIN_SET);

	(void)SPI2->DR;
	(void)SPI2->SR;

	while (1){

	}
	return 0;
}

