################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm" --include_path="D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm" --include_path="D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm/device" --include_path="D:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2837xd/driverlib" --include_path="D:/ti/c2000/C2000Ware_4_00_00_00/libraries/calibration/hrpwm/F2837xD/include" --include_path="D:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --define=_LAUNCHXL_F28379D --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-130098817: ../new.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/ti/ccs1210/ccs/utils/sysconfig_1.14.0/sysconfig_cli.bat" -s "D:/ti/c2000/C2000Ware_4_00_00_00/.metadata/sdk.json" -d "F2837xD" --script "D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm/new.syscfg" -o "syscfg" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-130098817 ../new.syscfg
syscfg/board.h: build-130098817
syscfg/pinmux.csv: build-130098817
syscfg/adc.dot: build-130098817
syscfg/: build-130098817

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm" --include_path="D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm" --include_path="D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm/device" --include_path="D:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2837xd/driverlib" --include_path="D:/ti/c2000/C2000Ware_4_00_00_00/libraries/calibration/hrpwm/F2837xD/include" --include_path="D:/ti/ccs1210/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --define=_LAUNCHXL_F28379D --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="D:/ti/CCS_workspace/adc_dma_soc_multiple_epwm/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


