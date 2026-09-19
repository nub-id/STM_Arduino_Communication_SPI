################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32f446re_GPIO.c \
../Src/STM32f446re_SPI_driver.c \
../Src/spi_senddata.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/STM32f446re_GPIO.o \
./Src/STM32f446re_SPI_driver.o \
./Src/spi_senddata.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/STM32f446re_GPIO.d \
./Src/STM32f446re_SPI_driver.d \
./Src/spi_senddata.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/STM32f446re_GPIO.cyclo ./Src/STM32f446re_GPIO.d ./Src/STM32f446re_GPIO.o ./Src/STM32f446re_GPIO.su ./Src/STM32f446re_SPI_driver.cyclo ./Src/STM32f446re_SPI_driver.d ./Src/STM32f446re_SPI_driver.o ./Src/STM32f446re_SPI_driver.su ./Src/spi_senddata.cyclo ./Src/spi_senddata.d ./Src/spi_senddata.o ./Src/spi_senddata.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

