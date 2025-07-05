/*
 * F28379D_my_fft.c
 *
 *  Created on: 2024年7月14日
 *      Author: Lenovo
 */
#include "F28379D_my_rfft.h"

//! \brief RFFT_ADC_F32_STRUCT object
//!
RFFT_ADC_F32_STRUCT rfft_adc;

//! \brief Handle to the RFFT_ADC_F32_STRUCT object
//!
RFFT_ADC_F32_STRUCT_Handle hnd_rfft_adc = &rfft_adc;

//! \brief RFFT_F32_STRUCT object
//!
RFFT_F32_STRUCT rfft;

//! \brief Handle to the RFFT_F32_STRUCT object
//!
RFFT_F32_STRUCT_Handle hnd_rfft = &rfft;


void Init_Rfft_F32_Struct(void)
{
    //Link the RFFT_ADC_F32_STRUCT to RFFT_F32_STRUCT. Tail pointer
    //of RFFT_ADC_F32_STRUCT is passed to the OutBuf pointer of
    //RFFT_F32_STRUCT
    hnd_rfft_adc->Tail = &(hnd_rfft->OutBuf);

    hnd_rfft->FFTSize   = RFFT_SIZE;         //FFT size
    hnd_rfft->FFTStages = RFFT_STAGES;       //FFT stages

    hnd_rfft_adc->InBuf = &RFFTin1Buff[0];   //Input buffer (12-bit ADC input)
    hnd_rfft->OutBuf    = &RFFToutBuff[0];   //Output buffer
    hnd_rfft->CosSinBuf = &RFFTF32Coef[0];   //Twiddle factor
    hnd_rfft->MagBuf    = &RFFTmagBuff[0];   //Magnitude output buffer
    hnd_rfft->PhaseBuf  = &RFFTphaseBuff[0]; //Phase output buffer

    RFFT_f32_sincostable(hnd_rfft);          //Calculate twiddle factor

    int i;

    for (i=0; i < RFFT_SIZE; i++){
        RFFToutBuff[i] = 0;                  //Clean up output buffer
    }

    for (i=0; i <= RFFT_SIZE/2; i++){
        RFFTmagBuff[i] = 0;                  //Clean up magnitude buffer
    }

    for (i=0; i < RFFT_SIZE/2; i++){
        RFFTphaseBuff[i] = 0;                //Clean up phase buffer
    }
}

// 进行一个新的尝试对于任意的一个满足长度的数组进行傅里叶变换
// 从逻辑上来判断这个函数完全可以使用了，它将可以实现对一个长度一致的数组进行傅里叶变换
// 而具体尝试还没有，可以在之后的工程融合文件中的那个尝试一下
void Rfft_F32(void)
{
//    //Link the RFFT_ADC_F32_STRUCT to RFFT_F32_STRUCT. Tail pointer
//    //of RFFT_ADC_F32_STRUCT is passed to the OutBuf pointer of
//    //RFFT_F32_STRUCT
//    hnd_rfft_adc->Tail = &(hnd_rfft->OutBuf);


//    // 这里可以修改傅里叶变换的规模
//    hnd_rfft->FFTSize   = RFFT_SIZE;         //FFT size
//    hnd_rfft->FFTStages = RFFT_STAGES;       //FFT stages

    // 修改下面这一行的地址可以修改传进来的需要傅里叶变换的参数
    hnd_rfft_adc->InBuf = &RFFTin1Buff[0];   //Input buffer (12-bit ADC input)

//    hnd_rfft->OutBuf    = &RFFToutBuff[0];   //Output buffer
//    hnd_rfft->CosSinBuf = &RFFTF32Coef[0];   //Twiddle factor
//    hnd_rfft->MagBuf    = &RFFTmagBuff[0];   //Magnitude output buffer
//    hnd_rfft->PhaseBuf  = &RFFTphaseBuff[0]; //Phase output buffer

//    RFFT_f32_sincostable(hnd_rfft);          //Calculate twiddle factor

    int i;

    for (i=0; i < RFFT_SIZE; i++){
        RFFToutBuff[i] = 0;                  //Clean up output buffer
    }

    for (i=0; i <= RFFT_SIZE/2; i++){
        RFFTmagBuff[i] = 0;                  //Clean up magnitude buffer
    }

    for (i=0; i < RFFT_SIZE/2; i++){
        RFFTphaseBuff[i] = 0;                //Clean up phase buffer
    }

    RFFT_adc_f32(hnd_rfft_adc);   // Calculate real FFT (12-bit ADC input)

    // TMU0 表示存在某种加速运算的加速器
    // 如果没有的话请使用 RFFT_f32_mag() 等函数
    RFFT_f32_mag_TMU0(hnd_rfft);        //Calculate magnitude
    RFFT_f32_phase_TMU0(hnd_rfft);      //Calculate phase

}

//
// 这个傅里叶算法可以实现计算频谱
// 如果有这么好的频谱信息还只能算出一个这样比较糟糕的频率
// 这能说这个频率计算的算法烂透了
//

float Caculate_Freq(void)
{
    float m;
    float m1, m2;
    m = RFFTmagBuff[1];

    int j = 0;
    int i;
    for(i=2;i<RFFT_SIZE/2+1;i++){
         if(RFFTmagBuff[i] > m){
            j = i;
            m = RFFTmagBuff[i];
        }
    }

    float t1, t2;
    t1 = RFFTmagBuff[j]/RFFTmagBuff[j+1];
    t2 = RFFTmagBuff[j-1]/RFFTmagBuff[j];

    if(RFFTmagBuff[j-1]>RFFTmagBuff[j+1])
    {
        m1 = ((float)j) * (j+1) * (t1*j -j-1)/(t1 + j*t1 - j);
        m2 = ((float)(j-1)) * j * (t2*j -t2+j)/(j*t2 +j-1);
    }
    else
    {
        m1 = ((float)j) * (j+1) * (t1*j +j+1)/(t1 + j*t1 + j);
        m2 = ((float)(j-1)) * j * (t2*j -t2-j)/(j*t2 -j+1);
    }

    m = sqrt((m1 + m2)/2);

    m = F_PER_SAMPLE * m;

    return m;
}

// 还没有完成
// 下面这个函数将会实现我们的幅频、相频特性曲线进行一个简化运算
// 在这个函数中，我们将会实现简化幅度谱、相位谱的功能
// 初步计划是将最大的幅度的那几个频率的波形进行写入
// 大概的大小是 5 个数组
// 也就是说 num 的取值一般是 5
// 这个内容，我是放在了对应的 H 文件中的宏定义之中
// 通过修改宏定义之中的设置就可以实现修改获取的信号
// 不过需要说明的是这里寻找到的谐波信号
// 其最小的幅度不应该小于其最大的信号的 Min_Max      0.1
// 其个数不应大于设定的频谱数目大小     Spectrum_Num 5
// 如果必要的话，可以考虑写一个排序算法
void simplify_mag_phase(float* mag, float* phase, float* freq, int num)
{
    float m;
    m = RFFTmagBuff[1];
    int j[Spectrum_Num];

    int k = 1;

    int i;
    // 寻找出幅度最大的频率信号
    for(i=2;i<RFFT_SIZE/2+1;i++)
    {
         if(RFFTmagBuff[i] > m)
         {
            j[0] = i;
            m = RFFTmagBuff[i];
         }
    }
    // 寻找出幅度大于最大信号 Min_Max 0.1 倍的频率信号
    for(i=0;i<RFFT_SIZE/2+1;i++)
    {
        if(RFFTmagBuff[i] > RFFTmagBuff[j[0]] * Min_Max && i != j[0])
        {
            j[k] = i;
            k++;
        }
    }

    float t1, t2;
    float m1, m2;
    // 遍历一遍所有的较大幅度的波形信号
    // 利用这个离散傅里叶变换的特殊算法，来提高精度
    for(i=0;i<k;i++)
    {
        t1 = RFFTmagBuff[j[i]]/RFFTmagBuff[j[i]+1];
        t2 = RFFTmagBuff[j[i]-1]/RFFTmagBuff[j[i]];

        if(RFFTmagBuff[j[i]-1]>RFFTmagBuff[j[i]+1])
        {
            m1 = ((float)j[i]) * (j[i]+1) * (t1*j[i] -j[i]-1)/(t1 + j[i]*t1 - j[i]);
            m2 = ((float)(j[i]-1)) * j[i] * (t2*j[i] -t2+j[i])/(j[i]*t2 +j[i]-1);
        }
        else
        {
            m1 = ((float)j[i]) * (j[i]+1) * (t1*j[i] +j[i]+1)/(t1 + j[i]*t1 + j[i]);
            m2 = ((float)(j[i]-1)) * j[i] * (t2*j[i] -t2-j[i])/(j[i]*t2 -j[i]+1);
        }
        freq[i] = sqrt((m1 + m2)/2) * F_PER_SAMPLE;
    }

    // 接下来，利用之前计算的比较精准的频率信息，来计算一下幅度与相位
    for(i=0;i<k;i++)
    {

    }
}





































// 定义 rfft 相关的变量名，并且给它们分配地址
#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata1")
#else
#pragma DATA_SECTION(RFFTin1Buff,"RFFTdata1")
#endif //__cplusplus
//! \brief FFT Calculation Buffer
//! \note The input buffer needs to be aligned to an 2N word boundary
//! \note If the number of FFT stages is odd, the result of the FFT will
//! be written to this buffer
//! \note this buffer takes N 12-bit ADC input, hence its defined as an
//! unsigned int array, but the FFT algorithm ping-pongs between input/
//! output buffers each stage, therefore this buffer needs to be able
//! to accommodate N floats and should be of size 2*RFFT_SIZE
uint16_t RFFTin1Buff[2*RFFT_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata2")
#else
#pragma DATA_SECTION(RFFTmagBuff,"RFFTdata2")
#endif //__cplusplus
//! \brief Magnitude Calculation Buffer
//!
float RFFTmagBuff[RFFT_SIZE/2+1];

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata2")
#else
#pragma DATA_SECTION(RFFTphaseBuff,"RFFTdata2")
#endif //__cplusplus
//! \brief Phase Calculation Buffer
//!
float RFFTphaseBuff[RFFT_SIZE/2];

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata3")
#else
#pragma DATA_SECTION(RFFToutBuff,"RFFTdata3")
#endif //__cplusplus
//! \brief FFT Calculation Buffer
//! \note If the number of FFT stages is even, the result of the FFT will
//! be written to this buffer
//!
float RFFToutBuff[RFFT_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION("RFFTdata4")
#else
#pragma DATA_SECTION(RFFTF32Coef,"RFFTdata4")
#endif //__cplusplus
//! \brief Twiddle Factors
//!
float RFFTF32Coef[RFFT_SIZE];

