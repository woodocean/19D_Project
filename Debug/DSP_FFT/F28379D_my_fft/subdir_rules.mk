################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DSP_FFT/F28379D_my_fft/%.obj: ../DSP_FFT/F28379D_my_fft/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 --include_path="D:/ti/CCS_workspace/workspace_FFT/test/DSP_FFT/dsp_FPU__include" --include_path="D:/ti/CCS_workspace/workspace_FFT/test/Init_Conclusion_my_lib/constant_data" --include_path="D:/ti/CCS_workspace/workspace_FFT/test/Init_Conclusion_my_lib/peripheral_control" --include_path="D:/ti/CCS_workspace/workspace_FFT/test/Init_Conclusion_my_lib/math" --include_path="D:/ti/CCS_workspace/workspace_FFT/test/Init_Conclusion_my_lib/include" --include_path="D:/ti/CCS_workspace/workspace_FFT/test/DSP_FFT/F28379D_my_fft" --include_path="D:/ti/CCS_workspace/workspace_FFT/test/DSP_FFT/dsp_FPU_common" --include_path="D:/ti/CCS_workspace/workspace_FFT/test/Init_Conclusion_common/include" --include_path="D:/ti/CCS_workspace/workspace_FFT/test/Init_Conclusion_headers/include" --include_path="D:/ti/CCS_workspace/workspace_FFT/test" --include_path="D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --advice:performance=all --define=CPU1 --define=_LAUNCHXL_F28379D --define=ADCA -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="DSP_FFT/F28379D_my_fft/$(basename $(<F)).d_raw" --obj_directory="DSP_FFT/F28379D_my_fft" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


