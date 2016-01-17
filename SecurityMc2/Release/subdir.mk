################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application2.c \
../Ex_EEPROM_I2C_24c256.c \
../dcmotor.c \
../i2c.c \
../keypad.c \
../lcd.c \
../password.c \
../timer0_normal.c \
../uart.c 

OBJS += \
./Application2.o \
./Ex_EEPROM_I2C_24c256.o \
./dcmotor.o \
./i2c.o \
./keypad.o \
./lcd.o \
./password.o \
./timer0_normal.o \
./uart.o 

C_DEPS += \
./Application2.d \
./Ex_EEPROM_I2C_24c256.d \
./dcmotor.d \
./i2c.d \
./keypad.d \
./lcd.d \
./password.d \
./timer0_normal.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


