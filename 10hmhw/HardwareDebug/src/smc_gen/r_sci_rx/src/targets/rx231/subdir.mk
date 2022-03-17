################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_sci_rx/src/targets/rx231/r_sci_rx231.c \
../src/smc_gen/r_sci_rx/src/targets/rx231/r_sci_rx231_data.c 

COMPILER_OBJS += \
src/smc_gen/r_sci_rx/src/targets/rx231/r_sci_rx231.obj \
src/smc_gen/r_sci_rx/src/targets/rx231/r_sci_rx231_data.obj 

C_DEPS += \
src/smc_gen/r_sci_rx/src/targets/rx231/r_sci_rx231.d \
src/smc_gen/r_sci_rx/src/targets/rx231/r_sci_rx231_data.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_sci_rx/src/targets/rx231/%.obj: ../src/smc_gen/r_sci_rx/src/targets/rx231/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_sci_rx\src\targets\rx231\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_sci_rx\src\targets\rx231\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_sci_rx\src\targets\rx231\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_sci_rx\src\targets\rx231\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_sci_rx\src\targets\rx231\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_sci_rx\src\targets\rx231\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

