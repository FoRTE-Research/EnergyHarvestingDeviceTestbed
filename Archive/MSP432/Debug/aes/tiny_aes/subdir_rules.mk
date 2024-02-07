################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
aes/tiny_aes/%.o: ../aes/tiny_aes/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/Applications/ti/ccs1210/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-gcc-7.2.1" -c -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__MSP432P401R__ -Dgcc -I"/Applications/ti/ccs1210/ccs/ccs_base/arm/include" -I"/Applications/ti/ccs1210/ccs/ccs_base/arm/include/CMSIS" -I"/Users/zeezooryu/workspace_v12/EmbeddedCrypto_MSP432" -I"/Applications/ti/ccs1210/ccs/tools/compiler/gcc-arm-none-eabi-7-2017-q4-major/arm-none-eabi/include" -Os -g -gdwarf-3 -gstrict-dwarf -Wall -MMD -MP -MF"aes/tiny_aes/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


