################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
dsp_FPU_source/%.obj: ../dsp_FPU_source/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/myccs/test/dsp_FPU__include" --include_path="D:/myccs/test/dsp_FPU_common" --include_path="D:/myccs/test/Init_Conclusion_common/include" --include_path="D:/myccs/test/Init_Conclusion_headers/include" --include_path="D:/myccs/test" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --define=CPU1 --define=ADCA -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="dsp_FPU_source/$(basename $(<F)).d_raw" --obj_directory="dsp_FPU_source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

dsp_FPU_source/%.obj: ../dsp_FPU_source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/myccs/test/dsp_FPU__include" --include_path="D:/myccs/test/dsp_FPU_common" --include_path="D:/myccs/test/Init_Conclusion_common/include" --include_path="D:/myccs/test/Init_Conclusion_headers/include" --include_path="D:/myccs/test" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --define=CPU1 --define=ADCA -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="dsp_FPU_source/$(basename $(<F)).d_raw" --obj_directory="dsp_FPU_source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


