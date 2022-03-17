################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include makefile.init

RM := rm -rf *.sni *.dbg *.lst *.lis *.lpp *.map *.x *.lbp *.bls *.libelf *.rel *.lbk *.abs *.mi *.jmp *.fsy *.ud *.udm 1st/*.abs 1st/*.jmp 1st/*.fsy

# All of the sources participating in the build are defined here
-include sources.mk
-include src/smc_gen/Config_CMT0/subdir.mk
-include src/smc_gen/r_sci_rx/src/targets/rx231/subdir.mk
-include src/smc_gen/r_datfrx_rx/src/subdir.mk
-include src/smc_gen/Config_MTU0/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_4/subdir.mk
-include src/smc_gen/r_pincfg/subdir.mk
-include src/smc_gen/r_byteq/src/subdir.mk
-include src/smc_gen/r_datfrx_rx/src/flash_type_4/subdir.mk
-include src/smc_gen/Config_CMT1/subdir.mk
-include src/smc_gen/Config_PORT/subdir.mk
-include src/smc_gen/r_bsp/board/generic_rx231/subdir.mk
-include src/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_3/subdir.mk
-include src/smc_gen/r_datfrx_rx/src/flash_type_1/subdir.mk
-include src/smc_gen/Config_CMT2/subdir.mk
-include src/smc_gen/r_flash_rx/src/subdir.mk
-include src/smc_gen/r_bsp/mcu/rx231/subdir.mk
-include src/smc_gen/r_bsp/mcu/all/subdir.mk
-include src/smc_gen/r_datfrx_rx/src/flash_type_2/subdir.mk
-include src/smc_gen/Config_CMT3/subdir.mk
-include src/smc_gen/Config_ICU/subdir.mk
-include src/smc_gen/Config_WDT/subdir.mk
-include src/smc_gen/r_rscan_rx/src/subdir.mk
-include src/smc_gen/r_flash_rx/src/flash_type_1/subdir.mk
-include src/smc_gen/general/subdir.mk
-include src/smc_gen/r_datfrx_rx/src/flash_type_3/subdir.mk
-include src/smc_gen/r_sci_rx/src/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif 
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif 
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif 
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif 
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif 
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif 
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif 
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif 
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif 
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif 
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif 
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif 
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif 
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif 
endif

ifneq ($(strip $(SRC_UPPER_SRCS)),)
ALL_ASMS += $(SRC_UPPER_SRCS) 
endif
ifneq ($(strip $(SRC_SRCS)),)
ALL_ASMS += $(SRC_SRCS) 
endif
ifneq ($(strip $(S_UPPER_SRCS)),)
ALL_ASMS += $(S_UPPER_SRCS) 
endif
ifneq ($(strip $(S_SRCS)),)
ALL_ASMS += $(S_SRCS) 
endif


-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables
LINKER_OUTPUT_OUTPUTS += \
Newver_MhwSlave_Code_00.abs

LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS += \
Newver_MhwSlave_Code_00.lib

CONVERTOR_OUTPUT_OUTPUTS += \
Newver_MhwSlave_Code_00.mot

OBJS := \
$(COMPILER_OBJS) \
$(INDIVIDUAL_COMPILER_OBJS) \
$(ASSEMBLER_OBJS) \
$(CUSTOM_OBJS)

# All Target
all: $(CONVERTOR_OUTPUT_OUTPUTS) Newver_MhwSlave_Code_00.x Newver_MhwSlave_Code_00.udm

	@echo 'Build complete.'

%.mot: $(LINKER_OUTPUT_OUTPUTS) Converter.sub
	@echo 'Invoking: Converter'
	@echo 'Building target:'
	@echo ConverterNewver_MhwSlave_Code_00.tmp=
	@sed -e "s/^/    /" "ConverterNewver_MhwSlave_Code_00.tmp"
	rlink -subcommand="ConverterNewver_MhwSlave_Code_00.tmp"
	@echo 'Finished building target:'
	@echo.


Newver_MhwSlave_Code_00.abs: $(OBJS)  $(ALL_ASMS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) 
	@echo 'Invoking: Linker'
	@echo LinkerNewver_MhwSlave_Code_00.tmp=
	@sed -e "s/^/    /" "LinkerNewver_MhwSlave_Code_00.tmp"
	rlink -subcommand="LinkerNewver_MhwSlave_Code_00.tmp"
	@echo 'Finished building:'
	@echo.


Newver_MhwSlave_Code_00.lib: 
	@echo 'Invoking: Library Generator'
	@echo LibraryGeneratorNewver_MhwSlave_Code_00.tmp=
	@sed -e "s/^/    /" "LibraryGeneratorNewver_MhwSlave_Code_00.tmp"
	lbgrx -subcommand="LibraryGeneratorNewver_MhwSlave_Code_00.tmp"
	@echo 'Finished building:'
	@echo.

Newver_MhwSlave_Code_00.x: Newver_MhwSlave_Code_00.abs
		-C:\Users\Pustake\.eclipse\com.renesas.platform_849575292\Utilities\\ccrx\renesas_cc_converter.exe Newver_MhwSlave_Code_00.abs Newver_MhwSlave_Code_00.x

Newver_MhwSlave_Code_00.udm: $(LINKER_OUTPUT_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	udcollector -subcommand=udSubcommand.tmp -output=Newver_MhwSlave_Code_00.udm

# Other Targets
clean:
	-$(RM) $(LINKER_OUTPUT_OUTPUTS) $(LIBRARY_GENERATOR_OUTPUTTYPE_OUTPUTS) $(CONVERTOR_OUTPUT_OUTPUTS)
	-rm -rf $(OBJS) $(C_DEPS) $(ASM_DEPS) $(DSP_DEPS) 
	-rm -rf src/smc_gen/Config_CMT0/*.asm src/smc_gen/Config_CMT0/*.p src/smc_gen/Config_CMT0/*.pp src/smc_gen/Config_CMT0/*.src src/smc_gen/Config_CMT0/*.jmp src/smc_gen/Config_CMT0/*.lst src/smc_gen/Config_CMT0/*.prn src/smc_gen/Config_CMT0/*.i src/smc_gen/Config_CMT0/*.ud 
	-rm -rf src/smc_gen/r_sci_rx/src/targets/rx231/*.asm src/smc_gen/r_sci_rx/src/targets/rx231/*.p src/smc_gen/r_sci_rx/src/targets/rx231/*.pp src/smc_gen/r_sci_rx/src/targets/rx231/*.src src/smc_gen/r_sci_rx/src/targets/rx231/*.jmp src/smc_gen/r_sci_rx/src/targets/rx231/*.lst src/smc_gen/r_sci_rx/src/targets/rx231/*.prn src/smc_gen/r_sci_rx/src/targets/rx231/*.i src/smc_gen/r_sci_rx/src/targets/rx231/*.ud 
	-rm -rf src/smc_gen/r_datfrx_rx/src/*.asm src/smc_gen/r_datfrx_rx/src/*.p src/smc_gen/r_datfrx_rx/src/*.pp src/smc_gen/r_datfrx_rx/src/*.src src/smc_gen/r_datfrx_rx/src/*.jmp src/smc_gen/r_datfrx_rx/src/*.lst src/smc_gen/r_datfrx_rx/src/*.prn src/smc_gen/r_datfrx_rx/src/*.i src/smc_gen/r_datfrx_rx/src/*.ud 
	-rm -rf src/smc_gen/Config_MTU0/*.asm src/smc_gen/Config_MTU0/*.p src/smc_gen/Config_MTU0/*.pp src/smc_gen/Config_MTU0/*.src src/smc_gen/Config_MTU0/*.jmp src/smc_gen/Config_MTU0/*.lst src/smc_gen/Config_MTU0/*.prn src/smc_gen/Config_MTU0/*.i src/smc_gen/Config_MTU0/*.ud 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_4/*.asm src/smc_gen/r_flash_rx/src/flash_type_4/*.p src/smc_gen/r_flash_rx/src/flash_type_4/*.pp src/smc_gen/r_flash_rx/src/flash_type_4/*.src src/smc_gen/r_flash_rx/src/flash_type_4/*.jmp src/smc_gen/r_flash_rx/src/flash_type_4/*.lst src/smc_gen/r_flash_rx/src/flash_type_4/*.prn src/smc_gen/r_flash_rx/src/flash_type_4/*.i src/smc_gen/r_flash_rx/src/flash_type_4/*.ud 
	-rm -rf src/smc_gen/r_pincfg/*.asm src/smc_gen/r_pincfg/*.p src/smc_gen/r_pincfg/*.pp src/smc_gen/r_pincfg/*.src src/smc_gen/r_pincfg/*.jmp src/smc_gen/r_pincfg/*.lst src/smc_gen/r_pincfg/*.prn src/smc_gen/r_pincfg/*.i src/smc_gen/r_pincfg/*.ud 
	-rm -rf src/smc_gen/r_byteq/src/*.asm src/smc_gen/r_byteq/src/*.p src/smc_gen/r_byteq/src/*.pp src/smc_gen/r_byteq/src/*.src src/smc_gen/r_byteq/src/*.jmp src/smc_gen/r_byteq/src/*.lst src/smc_gen/r_byteq/src/*.prn src/smc_gen/r_byteq/src/*.i src/smc_gen/r_byteq/src/*.ud 
	-rm -rf src/smc_gen/r_datfrx_rx/src/flash_type_4/*.asm src/smc_gen/r_datfrx_rx/src/flash_type_4/*.p src/smc_gen/r_datfrx_rx/src/flash_type_4/*.pp src/smc_gen/r_datfrx_rx/src/flash_type_4/*.src src/smc_gen/r_datfrx_rx/src/flash_type_4/*.jmp src/smc_gen/r_datfrx_rx/src/flash_type_4/*.lst src/smc_gen/r_datfrx_rx/src/flash_type_4/*.prn src/smc_gen/r_datfrx_rx/src/flash_type_4/*.i src/smc_gen/r_datfrx_rx/src/flash_type_4/*.ud 
	-rm -rf src/smc_gen/Config_CMT1/*.asm src/smc_gen/Config_CMT1/*.p src/smc_gen/Config_CMT1/*.pp src/smc_gen/Config_CMT1/*.src src/smc_gen/Config_CMT1/*.jmp src/smc_gen/Config_CMT1/*.lst src/smc_gen/Config_CMT1/*.prn src/smc_gen/Config_CMT1/*.i src/smc_gen/Config_CMT1/*.ud 
	-rm -rf src/smc_gen/Config_PORT/*.asm src/smc_gen/Config_PORT/*.p src/smc_gen/Config_PORT/*.pp src/smc_gen/Config_PORT/*.src src/smc_gen/Config_PORT/*.jmp src/smc_gen/Config_PORT/*.lst src/smc_gen/Config_PORT/*.prn src/smc_gen/Config_PORT/*.i src/smc_gen/Config_PORT/*.ud 
	-rm -rf src/smc_gen/r_bsp/board/generic_rx231/*.asm src/smc_gen/r_bsp/board/generic_rx231/*.p src/smc_gen/r_bsp/board/generic_rx231/*.pp src/smc_gen/r_bsp/board/generic_rx231/*.src src/smc_gen/r_bsp/board/generic_rx231/*.jmp src/smc_gen/r_bsp/board/generic_rx231/*.lst src/smc_gen/r_bsp/board/generic_rx231/*.prn src/smc_gen/r_bsp/board/generic_rx231/*.i src/smc_gen/r_bsp/board/generic_rx231/*.ud 
	-rm -rf src/*.asm src/*.p src/*.pp src/*.src src/*.jmp src/*.lst src/*.prn src/*.i src/*.ud 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_3/*.asm src/smc_gen/r_flash_rx/src/flash_type_3/*.p src/smc_gen/r_flash_rx/src/flash_type_3/*.pp src/smc_gen/r_flash_rx/src/flash_type_3/*.src src/smc_gen/r_flash_rx/src/flash_type_3/*.jmp src/smc_gen/r_flash_rx/src/flash_type_3/*.lst src/smc_gen/r_flash_rx/src/flash_type_3/*.prn src/smc_gen/r_flash_rx/src/flash_type_3/*.i src/smc_gen/r_flash_rx/src/flash_type_3/*.ud 
	-rm -rf src/smc_gen/r_datfrx_rx/src/flash_type_1/*.asm src/smc_gen/r_datfrx_rx/src/flash_type_1/*.p src/smc_gen/r_datfrx_rx/src/flash_type_1/*.pp src/smc_gen/r_datfrx_rx/src/flash_type_1/*.src src/smc_gen/r_datfrx_rx/src/flash_type_1/*.jmp src/smc_gen/r_datfrx_rx/src/flash_type_1/*.lst src/smc_gen/r_datfrx_rx/src/flash_type_1/*.prn src/smc_gen/r_datfrx_rx/src/flash_type_1/*.i src/smc_gen/r_datfrx_rx/src/flash_type_1/*.ud 
	-rm -rf src/smc_gen/Config_CMT2/*.asm src/smc_gen/Config_CMT2/*.p src/smc_gen/Config_CMT2/*.pp src/smc_gen/Config_CMT2/*.src src/smc_gen/Config_CMT2/*.jmp src/smc_gen/Config_CMT2/*.lst src/smc_gen/Config_CMT2/*.prn src/smc_gen/Config_CMT2/*.i src/smc_gen/Config_CMT2/*.ud 
	-rm -rf src/smc_gen/r_flash_rx/src/*.asm src/smc_gen/r_flash_rx/src/*.p src/smc_gen/r_flash_rx/src/*.pp src/smc_gen/r_flash_rx/src/*.src src/smc_gen/r_flash_rx/src/*.jmp src/smc_gen/r_flash_rx/src/*.lst src/smc_gen/r_flash_rx/src/*.prn src/smc_gen/r_flash_rx/src/*.i src/smc_gen/r_flash_rx/src/*.ud 
	-rm -rf src/smc_gen/r_bsp/mcu/rx231/*.asm src/smc_gen/r_bsp/mcu/rx231/*.p src/smc_gen/r_bsp/mcu/rx231/*.pp src/smc_gen/r_bsp/mcu/rx231/*.src src/smc_gen/r_bsp/mcu/rx231/*.jmp src/smc_gen/r_bsp/mcu/rx231/*.lst src/smc_gen/r_bsp/mcu/rx231/*.prn src/smc_gen/r_bsp/mcu/rx231/*.i src/smc_gen/r_bsp/mcu/rx231/*.ud 
	-rm -rf src/smc_gen/r_bsp/mcu/all/*.asm src/smc_gen/r_bsp/mcu/all/*.p src/smc_gen/r_bsp/mcu/all/*.pp src/smc_gen/r_bsp/mcu/all/*.src src/smc_gen/r_bsp/mcu/all/*.jmp src/smc_gen/r_bsp/mcu/all/*.lst src/smc_gen/r_bsp/mcu/all/*.prn src/smc_gen/r_bsp/mcu/all/*.i src/smc_gen/r_bsp/mcu/all/*.ud 
	-rm -rf src/smc_gen/r_datfrx_rx/src/flash_type_2/*.asm src/smc_gen/r_datfrx_rx/src/flash_type_2/*.p src/smc_gen/r_datfrx_rx/src/flash_type_2/*.pp src/smc_gen/r_datfrx_rx/src/flash_type_2/*.src src/smc_gen/r_datfrx_rx/src/flash_type_2/*.jmp src/smc_gen/r_datfrx_rx/src/flash_type_2/*.lst src/smc_gen/r_datfrx_rx/src/flash_type_2/*.prn src/smc_gen/r_datfrx_rx/src/flash_type_2/*.i src/smc_gen/r_datfrx_rx/src/flash_type_2/*.ud 
	-rm -rf src/smc_gen/Config_CMT3/*.asm src/smc_gen/Config_CMT3/*.p src/smc_gen/Config_CMT3/*.pp src/smc_gen/Config_CMT3/*.src src/smc_gen/Config_CMT3/*.jmp src/smc_gen/Config_CMT3/*.lst src/smc_gen/Config_CMT3/*.prn src/smc_gen/Config_CMT3/*.i src/smc_gen/Config_CMT3/*.ud 
	-rm -rf src/smc_gen/Config_ICU/*.asm src/smc_gen/Config_ICU/*.p src/smc_gen/Config_ICU/*.pp src/smc_gen/Config_ICU/*.src src/smc_gen/Config_ICU/*.jmp src/smc_gen/Config_ICU/*.lst src/smc_gen/Config_ICU/*.prn src/smc_gen/Config_ICU/*.i src/smc_gen/Config_ICU/*.ud 
	-rm -rf src/smc_gen/Config_WDT/*.asm src/smc_gen/Config_WDT/*.p src/smc_gen/Config_WDT/*.pp src/smc_gen/Config_WDT/*.src src/smc_gen/Config_WDT/*.jmp src/smc_gen/Config_WDT/*.lst src/smc_gen/Config_WDT/*.prn src/smc_gen/Config_WDT/*.i src/smc_gen/Config_WDT/*.ud 
	-rm -rf src/smc_gen/r_rscan_rx/src/*.asm src/smc_gen/r_rscan_rx/src/*.p src/smc_gen/r_rscan_rx/src/*.pp src/smc_gen/r_rscan_rx/src/*.src src/smc_gen/r_rscan_rx/src/*.jmp src/smc_gen/r_rscan_rx/src/*.lst src/smc_gen/r_rscan_rx/src/*.prn src/smc_gen/r_rscan_rx/src/*.i src/smc_gen/r_rscan_rx/src/*.ud 
	-rm -rf src/smc_gen/r_flash_rx/src/flash_type_1/*.asm src/smc_gen/r_flash_rx/src/flash_type_1/*.p src/smc_gen/r_flash_rx/src/flash_type_1/*.pp src/smc_gen/r_flash_rx/src/flash_type_1/*.src src/smc_gen/r_flash_rx/src/flash_type_1/*.jmp src/smc_gen/r_flash_rx/src/flash_type_1/*.lst src/smc_gen/r_flash_rx/src/flash_type_1/*.prn src/smc_gen/r_flash_rx/src/flash_type_1/*.i src/smc_gen/r_flash_rx/src/flash_type_1/*.ud 
	-rm -rf src/smc_gen/general/*.asm src/smc_gen/general/*.p src/smc_gen/general/*.pp src/smc_gen/general/*.src src/smc_gen/general/*.jmp src/smc_gen/general/*.lst src/smc_gen/general/*.prn src/smc_gen/general/*.i src/smc_gen/general/*.ud 
	-rm -rf src/smc_gen/r_datfrx_rx/src/flash_type_3/*.asm src/smc_gen/r_datfrx_rx/src/flash_type_3/*.p src/smc_gen/r_datfrx_rx/src/flash_type_3/*.pp src/smc_gen/r_datfrx_rx/src/flash_type_3/*.src src/smc_gen/r_datfrx_rx/src/flash_type_3/*.jmp src/smc_gen/r_datfrx_rx/src/flash_type_3/*.lst src/smc_gen/r_datfrx_rx/src/flash_type_3/*.prn src/smc_gen/r_datfrx_rx/src/flash_type_3/*.i src/smc_gen/r_datfrx_rx/src/flash_type_3/*.ud 
	-rm -rf src/smc_gen/r_sci_rx/src/*.asm src/smc_gen/r_sci_rx/src/*.p src/smc_gen/r_sci_rx/src/*.pp src/smc_gen/r_sci_rx/src/*.src src/smc_gen/r_sci_rx/src/*.jmp src/smc_gen/r_sci_rx/src/*.lst src/smc_gen/r_sci_rx/src/*.prn src/smc_gen/r_sci_rx/src/*.i src/smc_gen/r_sci_rx/src/*.ud 
	@echo
	@echo 'Clean complete.'

.PHONY: all clean  
-include ../makefile.targets