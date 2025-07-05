################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../fpu32/fft/CFFT_f32.asm \
../fpu32/fft/CFFT_f32_mag.asm \
../fpu32/fft/CFFT_f32_mag_TMU0.asm \
../fpu32/fft/CFFT_f32_phase.asm \
../fpu32/fft/CFFT_f32_phase_TMU0.asm \
../fpu32/fft/CFFT_f32_twiddleFactors.asm \
../fpu32/fft/CFFT_f32_win.asm \
../fpu32/fft/CFFT_f32i.asm \
../fpu32/fft/CFFT_f32it.asm \
../fpu32/fft/CFFT_f32s_mag.asm \
../fpu32/fft/CFFT_f32s_mag_TMU0.asm \
../fpu32/fft/CFFT_f32t.asm \
../fpu32/fft/CFFT_f32u.asm \
../fpu32/fft/CFFT_f32ut.asm \
../fpu32/fft/ICFFT_f32.asm \
../fpu32/fft/ICFFT_f32t.asm \
../fpu32/fft/RFFT_adc_f32.asm \
../fpu32/fft/RFFT_adc_f32u.asm \
../fpu32/fft/RFFT_f32.asm \
../fpu32/fft/RFFT_f32_adc_win.asm \
../fpu32/fft/RFFT_f32_mag.asm \
../fpu32/fft/RFFT_f32_mag_TMU0.asm \
../fpu32/fft/RFFT_f32_phase.asm \
../fpu32/fft/RFFT_f32_phase_TMU0.asm \
../fpu32/fft/RFFT_f32_twiddleFactors.asm \
../fpu32/fft/RFFT_f32_win.asm \
../fpu32/fft/RFFT_f32s_mag.asm \
../fpu32/fft/RFFT_f32s_mag_TMU0.asm \
../fpu32/fft/RFFT_f32u.asm \
../fpu32/fft/cfft_f32_brev.asm \
../fpu32/fft/cfft_f32_pack.asm \
../fpu32/fft/cfft_f32_unpack.asm 

C_SRCS += \
../fpu32/fft/CFFT_f32_sincostable.c \
../fpu32/fft/RFFT_f32_sincostable.c 

C_DEPS += \
./fpu32/fft/CFFT_f32_sincostable.d \
./fpu32/fft/RFFT_f32_sincostable.d 

OBJS += \
./fpu32/fft/CFFT_f32.obj \
./fpu32/fft/CFFT_f32_mag.obj \
./fpu32/fft/CFFT_f32_mag_TMU0.obj \
./fpu32/fft/CFFT_f32_phase.obj \
./fpu32/fft/CFFT_f32_phase_TMU0.obj \
./fpu32/fft/CFFT_f32_sincostable.obj \
./fpu32/fft/CFFT_f32_twiddleFactors.obj \
./fpu32/fft/CFFT_f32_win.obj \
./fpu32/fft/CFFT_f32i.obj \
./fpu32/fft/CFFT_f32it.obj \
./fpu32/fft/CFFT_f32s_mag.obj \
./fpu32/fft/CFFT_f32s_mag_TMU0.obj \
./fpu32/fft/CFFT_f32t.obj \
./fpu32/fft/CFFT_f32u.obj \
./fpu32/fft/CFFT_f32ut.obj \
./fpu32/fft/ICFFT_f32.obj \
./fpu32/fft/ICFFT_f32t.obj \
./fpu32/fft/RFFT_adc_f32.obj \
./fpu32/fft/RFFT_adc_f32u.obj \
./fpu32/fft/RFFT_f32.obj \
./fpu32/fft/RFFT_f32_adc_win.obj \
./fpu32/fft/RFFT_f32_mag.obj \
./fpu32/fft/RFFT_f32_mag_TMU0.obj \
./fpu32/fft/RFFT_f32_phase.obj \
./fpu32/fft/RFFT_f32_phase_TMU0.obj \
./fpu32/fft/RFFT_f32_sincostable.obj \
./fpu32/fft/RFFT_f32_twiddleFactors.obj \
./fpu32/fft/RFFT_f32_win.obj \
./fpu32/fft/RFFT_f32s_mag.obj \
./fpu32/fft/RFFT_f32s_mag_TMU0.obj \
./fpu32/fft/RFFT_f32u.obj \
./fpu32/fft/cfft_f32_brev.obj \
./fpu32/fft/cfft_f32_pack.obj \
./fpu32/fft/cfft_f32_unpack.obj 

ASM_DEPS += \
./fpu32/fft/CFFT_f32.d \
./fpu32/fft/CFFT_f32_mag.d \
./fpu32/fft/CFFT_f32_mag_TMU0.d \
./fpu32/fft/CFFT_f32_phase.d \
./fpu32/fft/CFFT_f32_phase_TMU0.d \
./fpu32/fft/CFFT_f32_twiddleFactors.d \
./fpu32/fft/CFFT_f32_win.d \
./fpu32/fft/CFFT_f32i.d \
./fpu32/fft/CFFT_f32it.d \
./fpu32/fft/CFFT_f32s_mag.d \
./fpu32/fft/CFFT_f32s_mag_TMU0.d \
./fpu32/fft/CFFT_f32t.d \
./fpu32/fft/CFFT_f32u.d \
./fpu32/fft/CFFT_f32ut.d \
./fpu32/fft/ICFFT_f32.d \
./fpu32/fft/ICFFT_f32t.d \
./fpu32/fft/RFFT_adc_f32.d \
./fpu32/fft/RFFT_adc_f32u.d \
./fpu32/fft/RFFT_f32.d \
./fpu32/fft/RFFT_f32_adc_win.d \
./fpu32/fft/RFFT_f32_mag.d \
./fpu32/fft/RFFT_f32_mag_TMU0.d \
./fpu32/fft/RFFT_f32_phase.d \
./fpu32/fft/RFFT_f32_phase_TMU0.d \
./fpu32/fft/RFFT_f32_twiddleFactors.d \
./fpu32/fft/RFFT_f32_win.d \
./fpu32/fft/RFFT_f32s_mag.d \
./fpu32/fft/RFFT_f32s_mag_TMU0.d \
./fpu32/fft/RFFT_f32u.d \
./fpu32/fft/cfft_f32_brev.d \
./fpu32/fft/cfft_f32_pack.d \
./fpu32/fft/cfft_f32_unpack.d 

OBJS__QUOTED += \
"fpu32\fft\CFFT_f32.obj" \
"fpu32\fft\CFFT_f32_mag.obj" \
"fpu32\fft\CFFT_f32_mag_TMU0.obj" \
"fpu32\fft\CFFT_f32_phase.obj" \
"fpu32\fft\CFFT_f32_phase_TMU0.obj" \
"fpu32\fft\CFFT_f32_sincostable.obj" \
"fpu32\fft\CFFT_f32_twiddleFactors.obj" \
"fpu32\fft\CFFT_f32_win.obj" \
"fpu32\fft\CFFT_f32i.obj" \
"fpu32\fft\CFFT_f32it.obj" \
"fpu32\fft\CFFT_f32s_mag.obj" \
"fpu32\fft\CFFT_f32s_mag_TMU0.obj" \
"fpu32\fft\CFFT_f32t.obj" \
"fpu32\fft\CFFT_f32u.obj" \
"fpu32\fft\CFFT_f32ut.obj" \
"fpu32\fft\ICFFT_f32.obj" \
"fpu32\fft\ICFFT_f32t.obj" \
"fpu32\fft\RFFT_adc_f32.obj" \
"fpu32\fft\RFFT_adc_f32u.obj" \
"fpu32\fft\RFFT_f32.obj" \
"fpu32\fft\RFFT_f32_adc_win.obj" \
"fpu32\fft\RFFT_f32_mag.obj" \
"fpu32\fft\RFFT_f32_mag_TMU0.obj" \
"fpu32\fft\RFFT_f32_phase.obj" \
"fpu32\fft\RFFT_f32_phase_TMU0.obj" \
"fpu32\fft\RFFT_f32_sincostable.obj" \
"fpu32\fft\RFFT_f32_twiddleFactors.obj" \
"fpu32\fft\RFFT_f32_win.obj" \
"fpu32\fft\RFFT_f32s_mag.obj" \
"fpu32\fft\RFFT_f32s_mag_TMU0.obj" \
"fpu32\fft\RFFT_f32u.obj" \
"fpu32\fft\cfft_f32_brev.obj" \
"fpu32\fft\cfft_f32_pack.obj" \
"fpu32\fft\cfft_f32_unpack.obj" 

C_DEPS__QUOTED += \
"fpu32\fft\CFFT_f32_sincostable.d" \
"fpu32\fft\RFFT_f32_sincostable.d" 

ASM_DEPS__QUOTED += \
"fpu32\fft\CFFT_f32.d" \
"fpu32\fft\CFFT_f32_mag.d" \
"fpu32\fft\CFFT_f32_mag_TMU0.d" \
"fpu32\fft\CFFT_f32_phase.d" \
"fpu32\fft\CFFT_f32_phase_TMU0.d" \
"fpu32\fft\CFFT_f32_twiddleFactors.d" \
"fpu32\fft\CFFT_f32_win.d" \
"fpu32\fft\CFFT_f32i.d" \
"fpu32\fft\CFFT_f32it.d" \
"fpu32\fft\CFFT_f32s_mag.d" \
"fpu32\fft\CFFT_f32s_mag_TMU0.d" \
"fpu32\fft\CFFT_f32t.d" \
"fpu32\fft\CFFT_f32u.d" \
"fpu32\fft\CFFT_f32ut.d" \
"fpu32\fft\ICFFT_f32.d" \
"fpu32\fft\ICFFT_f32t.d" \
"fpu32\fft\RFFT_adc_f32.d" \
"fpu32\fft\RFFT_adc_f32u.d" \
"fpu32\fft\RFFT_f32.d" \
"fpu32\fft\RFFT_f32_adc_win.d" \
"fpu32\fft\RFFT_f32_mag.d" \
"fpu32\fft\RFFT_f32_mag_TMU0.d" \
"fpu32\fft\RFFT_f32_phase.d" \
"fpu32\fft\RFFT_f32_phase_TMU0.d" \
"fpu32\fft\RFFT_f32_twiddleFactors.d" \
"fpu32\fft\RFFT_f32_win.d" \
"fpu32\fft\RFFT_f32s_mag.d" \
"fpu32\fft\RFFT_f32s_mag_TMU0.d" \
"fpu32\fft\RFFT_f32u.d" \
"fpu32\fft\cfft_f32_brev.d" \
"fpu32\fft\cfft_f32_pack.d" \
"fpu32\fft\cfft_f32_unpack.d" 

ASM_SRCS__QUOTED += \
"../fpu32/fft/CFFT_f32.asm" \
"../fpu32/fft/CFFT_f32_mag.asm" \
"../fpu32/fft/CFFT_f32_mag_TMU0.asm" \
"../fpu32/fft/CFFT_f32_phase.asm" \
"../fpu32/fft/CFFT_f32_phase_TMU0.asm" \
"../fpu32/fft/CFFT_f32_twiddleFactors.asm" \
"../fpu32/fft/CFFT_f32_win.asm" \
"../fpu32/fft/CFFT_f32i.asm" \
"../fpu32/fft/CFFT_f32it.asm" \
"../fpu32/fft/CFFT_f32s_mag.asm" \
"../fpu32/fft/CFFT_f32s_mag_TMU0.asm" \
"../fpu32/fft/CFFT_f32t.asm" \
"../fpu32/fft/CFFT_f32u.asm" \
"../fpu32/fft/CFFT_f32ut.asm" \
"../fpu32/fft/ICFFT_f32.asm" \
"../fpu32/fft/ICFFT_f32t.asm" \
"../fpu32/fft/RFFT_adc_f32.asm" \
"../fpu32/fft/RFFT_adc_f32u.asm" \
"../fpu32/fft/RFFT_f32.asm" \
"../fpu32/fft/RFFT_f32_adc_win.asm" \
"../fpu32/fft/RFFT_f32_mag.asm" \
"../fpu32/fft/RFFT_f32_mag_TMU0.asm" \
"../fpu32/fft/RFFT_f32_phase.asm" \
"../fpu32/fft/RFFT_f32_phase_TMU0.asm" \
"../fpu32/fft/RFFT_f32_twiddleFactors.asm" \
"../fpu32/fft/RFFT_f32_win.asm" \
"../fpu32/fft/RFFT_f32s_mag.asm" \
"../fpu32/fft/RFFT_f32s_mag_TMU0.asm" \
"../fpu32/fft/RFFT_f32u.asm" \
"../fpu32/fft/cfft_f32_brev.asm" \
"../fpu32/fft/cfft_f32_pack.asm" \
"../fpu32/fft/cfft_f32_unpack.asm" 

C_SRCS__QUOTED += \
"../fpu32/fft/CFFT_f32_sincostable.c" \
"../fpu32/fft/RFFT_f32_sincostable.c" 


