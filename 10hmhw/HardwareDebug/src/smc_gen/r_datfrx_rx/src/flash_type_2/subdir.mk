################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/smc_gen/r_datfrx_rx/src/flash_type_2/r_datf_crc.c \
../src/smc_gen/r_datfrx_rx/src/flash_type_2/r_dispatch_2.c \
../src/smc_gen/r_datfrx_rx/src/flash_type_2/r_dm_2.c 

COMPILER_OBJS += \
src/smc_gen/r_datfrx_rx/src/flash_type_2/r_datf_crc.obj \
src/smc_gen/r_datfrx_rx/src/flash_type_2/r_dispatch_2.obj \
src/smc_gen/r_datfrx_rx/src/flash_type_2/r_dm_2.obj 

C_DEPS += \
src/smc_gen/r_datfrx_rx/src/flash_type_2/r_datf_crc.d \
src/smc_gen/r_datfrx_rx/src/flash_type_2/r_dispatch_2.d \
src/smc_gen/r_datfrx_rx/src/flash_type_2/r_dm_2.d 

# Each subdirectory must supply rules for building sources it contributes
src/smc_gen/r_datfrx_rx/src/flash_type_2/%.obj: ../src/smc_gen/r_datfrx_rx/src/flash_type_2/%.c 
	@echo 'Scanning and building file: $<'
	@echo 'Invoking: Scanner and Compiler'
	@echo src\smc_gen\r_datfrx_rx\src\flash_type_2\cDepSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_datfrx_rx\src\flash_type_2\cDepSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_datfrx_rx\src\flash_type_2\cDepSubCommand.tmp" -output=dep="$(@:%.obj=%.d)"  -MT="$(@:%.d=%.obj)"  -MT="$(@:%.obj=%.d)" "$<"
	@echo src\smc_gen\r_datfrx_rx\src\flash_type_2\cSubCommand.tmp=
	@sed -e "s/^/ /" "src\smc_gen\r_datfrx_rx\src\flash_type_2\cSubCommand.tmp"
	ccrx -subcommand="src\smc_gen\r_datfrx_rx\src\flash_type_2\cSubCommand.tmp" "$<"
	@echo 'Finished Scanning and building: $<'
	@echo.

