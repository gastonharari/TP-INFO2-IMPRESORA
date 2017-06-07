################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver_LPC1769/DR_EINT.c \
../Driver_LPC1769/DR_PLL.c \
../Driver_LPC1769/DR_SysTick.c \
../Driver_LPC1769/DR_adc.c \
../Driver_LPC1769/DR_gpio.c \
../Driver_LPC1769/DR_pinsel.c \
../Driver_LPC1769/DR_timer0123.c \
../Driver_LPC1769/DR_uart.c 

OBJS += \
./Driver_LPC1769/DR_EINT.o \
./Driver_LPC1769/DR_PLL.o \
./Driver_LPC1769/DR_SysTick.o \
./Driver_LPC1769/DR_adc.o \
./Driver_LPC1769/DR_gpio.o \
./Driver_LPC1769/DR_pinsel.o \
./Driver_LPC1769/DR_timer0123.o \
./Driver_LPC1769/DR_uart.o 

C_DEPS += \
./Driver_LPC1769/DR_EINT.d \
./Driver_LPC1769/DR_PLL.d \
./Driver_LPC1769/DR_SysTick.d \
./Driver_LPC1769/DR_adc.d \
./Driver_LPC1769/DR_gpio.d \
./Driver_LPC1769/DR_pinsel.d \
./Driver_LPC1769/DR_timer0123.d \
./Driver_LPC1769/DR_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Driver_LPC1769/%.o: ../Driver_LPC1769/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Aplicacion" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Driver_Infotronic" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Driver_LPC1769" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Primitivas" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


