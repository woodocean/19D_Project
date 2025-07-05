################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/device" --include_path="D:/ti/c2000/C2000Ware_5_05_00_00/driverlib/f2837xd/driverlib/" --include_path="D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/include/inc2" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/include/inc1" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32/vector" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32/utility" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32/filter" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32/fft" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/common" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/source2" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/source" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/source2/inc" --define=DEBUG --define=CPU1 --define=_DUAL_HEADERS --define=_LAUNCHXL_F28379D --define=ADCA --define=__TMS320C28XX_TMU__ --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1535500657: ../new.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"D:/ti/ccs2020/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/new.syscfg" -o "syscfg" -s "D:/ti/c2000/C2000Ware_5_05_00_00/.metadata/sdk.json" -d "F2837xD" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1535500657 ../new.syscfg
syscfg/board.h: build-1535500657
syscfg/board.cmd.genlibs: build-1535500657
syscfg/board.opt: build-1535500657
syscfg/board.json: build-1535500657
syscfg/pinmux.csv: build-1535500657
syscfg/adc.dot: build-1535500657
syscfg/c2000ware_libraries.cmd.genlibs: build-1535500657
syscfg/c2000ware_libraries.opt: build-1535500657
syscfg/c2000ware_libraries.c: build-1535500657
syscfg/c2000ware_libraries.h: build-1535500657
syscfg/clocktree.h: build-1535500657
syscfg: build-1535500657

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/device" --include_path="D:/ti/c2000/C2000Ware_5_05_00_00/driverlib/f2837xd/driverlib/" --include_path="D:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/include/inc2" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/include/inc1" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32/vector" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32/utility" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32/filter" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32/fft" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/fpu32" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/common" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/source2" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/source" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/source2/inc" --define=DEBUG --define=CPU1 --define=_DUAL_HEADERS --define=_LAUNCHXL_F28379D --define=ADCA --define=__TMS320C28XX_TMU__ --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="D:/ti/CCS_workspace/workspace_dual/empty_driverlib_project_v1/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


