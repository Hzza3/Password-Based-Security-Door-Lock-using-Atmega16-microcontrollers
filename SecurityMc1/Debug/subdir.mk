################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application1.c \
../IntEEPROM.c \
../keypad.c \
../lcd.c \
../password.c \
../timer0_normal.c \
../uart.c 

OBJS += \
./Application1.o \
./IntEEPROM.o \
./keypad.o \
./lcd.o \
./password.o \
./timer0_normal.o \
./uart.o 

C_DEPS += \
./Application1.d \
./IntEEPROM.d \
./keypad.d \
./lcd.d \
./password.d \
./timer0_normal.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


