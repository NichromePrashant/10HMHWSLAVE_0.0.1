################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/ADC_CS5532.c \
../src/Auto_Tare.c \
../src/Calibration.c \
../src/Flash.c \
../src/Manual_OP.c \
../src/Newver_MhwSlave_Code_01.c \
../src/PWM.c \
../src/Peripheral.c \
../src/RUN_OP.c \
../src/Stepper_Motor.c \
../src/Timer.c \
../src/can.c 

COMPILER_OBJS += \
src/ADC_CS5532.obj \
src/Auto_Tare.obj \
src/Calibration.obj \
src/Flash.obj \
src/Manual_OP.obj \
src/Newver_MhwSlave_Code_01.obj \
src/PWM.obj \
src/Peripheral.obj \
src/RUN_OP.obj \
src/Stepper_Motor.obj \
src/Timer.obj \
src/can.obj 

C_DEPS += \
src/ADC_CS5532.d \
src/Auto_Tare.d \
src/Calibration.d \
src/Flash.d \
src/Manual_OP.d \
src/Newver_MhwSlave_Code_01.d \
src/PWM.d \
src/Peripheral.d \
src/RUN_OP.d \
src/Stepper_Motor.d \
src/Timer.d \
src/can.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\cDepSubCommand.tmp"
	ccrx -subcommand="src\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\cSubCommand.tmp"
	ccrx -subcommand="src\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

