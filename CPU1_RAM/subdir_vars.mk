################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../2837xD_RAM_lnk_cpu1.cmd 

SYSCFG_SRCS += \
../new.syscfg 

LIB_SRCS += \
D:/ti/c2000/C2000Ware_4_00_00_00/libraries/calibration/hrpwm/f2837xd/lib/SFO_v8_fpu_lib_build_c28_driverlib.lib \
D:/ti/c2000/C2000Ware_4_00_00_00/driverlib/f2837xd/driverlib/ccs/Debug/driverlib.lib 

C_SRCS += \
../adc_dma_multiple_soc_epwm.c \
../gpio.c \
./syscfg/board.c 

GEN_FILES += \
./syscfg/board.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./adc_dma_multiple_soc_epwm.d \
./gpio.d \
./syscfg/board.d 

OBJS += \
./adc_dma_multiple_soc_epwm.obj \
./gpio.obj \
./syscfg/board.obj 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/pinmux.csv \
./syscfg/adc.dot 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"adc_dma_multiple_soc_epwm.obj" \
"gpio.obj" \
"syscfg\board.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\pinmux.csv" \
"syscfg\adc.dot" 

C_DEPS__QUOTED += \
"adc_dma_multiple_soc_epwm.d" \
"gpio.d" \
"syscfg\board.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" 

C_SRCS__QUOTED += \
"../adc_dma_multiple_soc_epwm.c" \
"../gpio.c" \
"./syscfg/board.c" 

SYSCFG_SRCS__QUOTED += \
"../new.syscfg" 


