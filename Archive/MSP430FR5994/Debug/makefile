################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./aes/aes.obj" \
"./aes/gladman/aes_modes.obj" \
"./aes/gladman/aesaux.obj" \
"./aes/gladman/aescrypt.obj" \
"./aes/gladman/aeskey.obj" \
"./aes/gladman/aestab.obj" \
"./aes/gladman/aestst.obj" \
"./mac/cmac/cmac.obj" \
"./mac/cmac/main.obj" \
"./mac/cmac/utils.obj" \
"../lnk_msp430fr5994.cmd" \
$(GEN_CMDS__FLAG) \
-llibmpu_init.a \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include aes/subdir_vars.mk
-include aes/gladman/subdir_vars.mk
-include mac/cmac/subdir_vars.mk
-include subdir_rules.mk
-include aes/subdir_rules.mk
-include aes/gladman/subdir_rules.mk
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
EmbeddedCrypto_MSP430FR5994.out \

EXE_OUTPUTS__QUOTED += \
"EmbeddedCrypto_MSP430FR5994.out" \

BIN_OUTPUTS += \
EmbeddedCrypto_MSP430FR5994.hex \

BIN_OUTPUTS__QUOTED += \
"EmbeddedCrypto_MSP430FR5994.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "EmbeddedCrypto_MSP430FR5994.out"

# Tool invocations
EmbeddedCrypto_MSP430FR5994.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"/Applications/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --data_model=restricted -O0 --opt_for_speed=5 --use_hw_mpy=F5 --advice:power="all" --advice:hw_config=all --define=__MSP430FR5994__ --define=_MPU_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"EmbeddedCrypto_MSP430FR5994.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"/Applications/ti/ccs1210/ccs/ccs_base/msp430/include" -i"/Applications/ti/ccs1210/ccs/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"/Applications/ti/ccs1210/ccs/ccs_base/msp430/lib/FR59xx" -i"/Applications/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/lib" -i"/Applications/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --priority --reread_libs --define=_MPU_ENABLE --diag_wrap=off --display_error_number --warn_sections --xml_link_info="EmbeddedCrypto_MSP430FR5994_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "EmbeddedCrypto_MSP430FR5994.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

EmbeddedCrypto_MSP430FR5994.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: MSP430 Hex Utility'
	"/Applications/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/hex430" --memwidth=8 --romwidth=8 --diag_wrap=off -o "EmbeddedCrypto_MSP430FR5994.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "aes/aes.obj" "aes/gladman/aes_modes.obj" "aes/gladman/aesaux.obj" "aes/gladman/aescrypt.obj" "aes/gladman/aeskey.obj" "aes/gladman/aestab.obj" "aes/gladman/aestst.obj" "mac/cmac/cmac.obj" "mac/cmac/main.obj" "mac/cmac/utils.obj" 
	-$(RM) "aes/aes.d" "aes/gladman/aes_modes.d" "aes/gladman/aesaux.d" "aes/gladman/aescrypt.d" "aes/gladman/aeskey.d" "aes/gladman/aestab.d" "aes/gladman/aestst.d" "mac/cmac/cmac.d" "mac/cmac/main.d" "mac/cmac/utils.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

