/*
 * F28379D_my_rfft.h
 *
 *  Created on: 2024Äê7ÔÂ14ÈÕ
 *      Author: Lenovo
 */

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the 512-sample RFFT ADC example
//! \return returns a 1
//!
//! This program shows how to compute the real FFT, magnitude and phase of
//! data from the 12-bit ADC input. The input buffer must be aligned to a
//! 2N word boundary if using RFFT_f32.
//! Data section alignment (#pragma ...) is not necessary for RFFT_adc_f32u
//! but necessary when running RFFT_adc_f32.  However, using the unaligned
//! version will reduce cycle performance of the algorithm.
//!
//! The minimum number of stages is 3. When the number of stages is more
//! than 9, the quantization error would be significant and not recommended.
//! This example will sample an EPWM channel over an ADC channel and run the
//! RFFT on a real signal.
//!
//! RFFT_F32_STRUCT is a structure defined as:
//!
//!    typedef struct {
//!      float  *InBuf;
//!      float  *OutBuf;
//!      float  *CosSinBuf;
//!      float  *MagBuf;
//!      float  *PhaseBuf;
//!      uint16_t FFTSize;
//!      uint16_t FFTStages;
//!    } RFFT_F32_STRUCT;
//!
//! RFFT_ADC_F32_STRUCT is defined as:
//!    typedef struct {
//!      uint16_t   *InBuf;
//!      void       *Tail;
//!    } RFFT_ADC_F32_STRUCT;
//!
//!  ASSUMPTIONS:
//!
//! -# OutBuf of RFFT_F32_STRUCT has to be passed to Tail of
//!    RFFT_ADC_F32_STRUCT
//! -# Input signal is stored in Signal.asm
//! -# FFTSize must be a power of 2 (32, 64, 128, etc)
//! -# FFTSize must be greater or equal to 32
//! -# FFTStages must be log2(FFTSize)
//! -# InBuf, OutBuf, CosSinBuf are FFTSize in length
//! -# Magnitude buffer is FFTSize/2+1 in length
//! -# Phase buffer is FFTSize/2 in length
//!
//! Watch Variables:
//!
//! -# InBuf(RFFT_ADC_F32_STRUCT)    Input buffer
//! -# InBuf(RFFT_F32_STRUCT)        Not used
//! -# Tail                          Stored the address of OutBuf
//! -# OutBuf                        Output buffer
//! -# CosSinBuf                     Twiddle factor buffer
//! -# MagBuf                        Magnitude buffer
//! -# PhaseBuf                      Phase buffer
//! -# j                             Index of normalized digital frequency component
//! -# freq                          Real analog frequency of raw signal
//!








#ifndef DSP_FFT_F28379D_MY_FFT_F28379D_MY_RFFT_H_
#define DSP_FFT_F28379D_MY_FFT_F28379D_MY_RFFT_H_


#include "fpu_rfft.h"            // Main include file
#include "math.h"

#include "F28379D_my_lib.h"

#define RFFT_STAGES     9
#define RFFT_SIZE       (1 << RFFT_STAGES)
#define F_PER_SAMPLE    (ADC_SAMPLING_FREQ/(float)RFFT_SIZE)
#define USE_TEST_INPUT  1 // If not in test mode, be sure to exclude signal.asm
                          // from the build
#define EPSILON         0.1



extern uint16_t RFFTin1Buff[2*RFFT_SIZE];
extern float RFFTmagBuff[RFFT_SIZE/2+1];
extern float RFFTphaseBuff[RFFT_SIZE/2];
extern float RFFToutBuff[RFFT_SIZE];
extern float RFFTF32Coef[RFFT_SIZE];


extern RFFT_ADC_F32_STRUCT rfft_adc;
extern RFFT_ADC_F32_STRUCT_Handle hnd_rfft_adc;

extern RFFT_F32_STRUCT rfft;
extern RFFT_F32_STRUCT_Handle hnd_rfft;

extern void Init_Rfft_F32_Struct(void);

extern float Caculate_Freq(void);






#define Spectrum_Num     5
#define Min_Max          0.1
extern void Rfft_F32(void);

#endif /* DSP_FFT_F28379D_MY_FFT_F28379D_MY_RFFT_H_ */
