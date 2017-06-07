################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver_Infotronic/DR_7seg.c \
../Driver_Infotronic/DR_DigSig.c \
../Driver_Infotronic/DR_MPP.c \
../Driver_Infotronic/DR_Teclado.c \
../Driver_Infotronic/Inicializacion.c 

OBJS += \
./Driver_Infotronic/DR_7seg.o \
./Driver_Infotronic/DR_DigSig.o \
./Driver_Infotronic/DR_MPP.o \
./Driver_Infotronic/DR_Teclado.o \
./Driver_Infotronic/Inicializacion.o 

C_DEPS += \
./Driver_Infotronic/DR_7seg.d \
./Driver_Infotronic/DR_DigSig.d \
./Driver_Infotronic/DR_MPP.d \
./Driver_Infotronic/DR_Teclado.d \
./Driver_Infotronic/Inicializacion.d 


# Each subdirectory must supply rules for building sources it contributes
Driver_Infotronic/%.o: ../Driver_Infotronic/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Aplicacion" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Driver_Infotronic" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Driver_LPC1769" -I"C:\Users\santi\Documents\Santi\Facultad\Info2\Infotronic\TPO\Primitivas" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


