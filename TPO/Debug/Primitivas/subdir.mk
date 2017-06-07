################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Primitivas/PR_7seg.c \
../Primitivas/PR_BT.c \
../Primitivas/PR_Teclado.c \
../Primitivas/PR_Timer.c \
../Primitivas/PR_extras.c \
../Primitivas/PR_parcial.c \
../Primitivas/PR_uart.c 

OBJS += \
./Primitivas/PR_7seg.o \
./Primitivas/PR_BT.o \
./Primitivas/PR_Teclado.o \
./Primitivas/PR_Timer.o \
./Primitivas/PR_extras.o \
./Primitivas/PR_parcial.o \
./Primitivas/PR_uart.o 

C_DEPS += \
./Primitivas/PR_7seg.d \
./Primitivas/PR_BT.d \
./Primitivas/PR_Teclado.d \
./Primitivas/PR_Timer.d \
./Primitivas/PR_extras.d \
./Primitivas/PR_parcial.d \
./Primitivas/PR_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Primitivas/%.o: ../Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Aplicacion" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Driver_Infotronic" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Driver_LPC1769" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Primitivas" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


