################################################################################
# Automatically-generated file. Do not edit!
################################################################################

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./cpu.o" \
"./interrupt.o" \
"./startup_msp432p401r_gcc.o" \
"./system_msp432p401r.o" \
"./systick.o" \
"./aes/aes.o" \
"./aes/mbedtls/aes.o" \
"./mac/cmac/cmac.o" \
"./mac/cmac/main.o" \
"./mac/cmac/utils.o" \
-Wl,-T"../msp432p401r.lds" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-lgcc \
-lnosys \
-lc \
-Wl,--end-group \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include aes/subdir_vars.mk
-include aes/mbedtls/subdir_vars.mk
-include mac/cmac/subdir_vars.mk
-include subdir_rules.mk
-include aes/subdir_rules.mk
-include aes/mbedtls/subdir_rules.mk
-include mac/cmac/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
EmbeddedCrypto_MSP432P401R.out \

EXE_OUTPUTS__QUOTED += \
"EmbeddedCrypto_MSP432P401R.out" \

BIN_OUTPUTS += \
EmbeddedCrypto_MSP432P401R.hex \

BIN_OUTPUTS__QUOTED += \
"EmbeddedCrypto_MSP432P401R.hex" \


# All Target
all: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "EmbeddedCrypto_MSP432P401R.out"

# Tool invocations
EmbeddedCrypto_MSP432P401R.out: $(OBJS) $(LDS_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: GNU Linker'
	"" -Wl,-Map,"EmbeddedCrypto_MSP432P401R.map" -mthumb -g -gstrict-dwarf -Wall -o"EmbeddedCrypto_MSP432P401R.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

EmbeddedCrypto_MSP432P401R.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: GNU Objcopy Utility'
	""  $(EXE_OUTPUTS__QUOTED) "EmbeddedCrypto_MSP432P401R.hex"
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "cpu.o" "interrupt.o" "startup_msp432p401r_gcc.o" "system_msp432p401r.o" "systick.o" "aes/aes.o" "aes/mbedtls/aes.o" "mac/cmac/cmac.o" "mac/cmac/main.o" "mac/cmac/utils.o" 
	-$(RM) "cpu.d" "interrupt.d" "startup_msp432p401r_gcc.d" "system_msp432p401r.d" "systick.d" "aes/aes.d" "aes/mbedtls/aes.d" "mac/cmac/cmac.d" "mac/cmac/main.d" "mac/cmac/utils.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

