################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
aes/mbedtls/%.obj: ../aes/mbedtls/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/Applications/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/bin/cl430" -vmspx --data_model=restricted -O0 --opt_for_speed=0 --use_hw_mpy=F5 --include_path="/Applications/ti/ccs1210/ccs/ccs_base/msp430/include" --include_path="/Users/zeezooryu/workspace_v12/EmbeddedCrypto_MSP430F5529LP" --include_path="/Applications/ti/ccs1210/ccs/tools/compiler/ti-cgt-msp430_21.6.0.LTS/include" --advice:power=all --define=__MSP430F5529__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="aes/mbedtls/$(basename $(<F)).d_raw" --obj_directory="aes/mbedtls" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

