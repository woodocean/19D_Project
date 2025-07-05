/*
 * F28379D_my_fft.c
 *
 *  Created on: 2024��7��14��
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

// ����һ���µĳ��Զ��������һ�����㳤�ȵ�������и���Ҷ�任
// ���߼������ж����������ȫ����ʹ���ˣ���������ʵ�ֶ�һ������һ�µ�������и���Ҷ�任
// �����峢�Ի�û�У�������֮��Ĺ����ں��ļ��е��Ǹ�����һ��
void Rfft_F32(void)
{
//    //Link the RFFT_ADC_F32_STRUCT to RFFT_F32_STRUCT. Tail pointer
//    //of RFFT_ADC_F32_STRUCT is passed to the OutBuf pointer of
//    //RFFT_F32_STRUCT
//    hnd_rfft_adc->Tail = &(hnd_rfft->OutBuf);


//    // ��������޸ĸ���Ҷ�任�Ĺ�ģ
//    hnd_rfft->FFTSize   = RFFT_SIZE;         //FFT size
//    hnd_rfft->FFTStages = RFFT_STAGES;       //FFT stages

    // �޸�������һ�еĵ�ַ�����޸Ĵ���������Ҫ����Ҷ�任�Ĳ���
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

    // TMU0 ��ʾ����ĳ�ּ�������ļ�����
    // ���û�еĻ���ʹ�� RFFT_f32_mag() �Ⱥ���
    RFFT_f32_mag_TMU0(hnd_rfft);        //Calculate magnitude
    RFFT_f32_phase_TMU0(hnd_rfft);      //Calculate phase

}

//
// �������Ҷ�㷨����ʵ�ּ���Ƶ��
// �������ô�õ�Ƶ����Ϣ��ֻ�����һ�������Ƚ�����Ƶ��
// ����˵���Ƶ�ʼ�����㷨��͸��
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

// ��û�����
// ���������������ʵ�����ǵķ�Ƶ����Ƶ�������߽���һ��������
// ����������У����ǽ���ʵ�ּ򻯷����ס���λ�׵Ĺ���
// �����ƻ��ǽ����ķ��ȵ��Ǽ���Ƶ�ʵĲ��ν���д��
// ��ŵĴ�С�� 5 ������
// Ҳ����˵ num ��ȡֵһ���� 5
// ������ݣ����Ƿ����˶�Ӧ�� H �ļ��еĺ궨��֮��
// ͨ���޸ĺ궨��֮�е����þͿ���ʵ���޸Ļ�ȡ���ź�
// ������Ҫ˵����������Ѱ�ҵ���г���ź�
// ����С�ķ��Ȳ�Ӧ��С���������źŵ� Min_Max      0.1
// �������Ӧ�����趨��Ƶ����Ŀ��С     Spectrum_Num 5
// �����Ҫ�Ļ������Կ���дһ�������㷨
void simplify_mag_phase(float* mag, float* phase, float* freq, int num)
{
    float m;
    m = RFFTmagBuff[1];
    int j[Spectrum_Num];

    int k = 1;

    int i;
    // Ѱ�ҳ���������Ƶ���ź�
    for(i=2;i<RFFT_SIZE/2+1;i++)
    {
         if(RFFTmagBuff[i] > m)
         {
            j[0] = i;
            m = RFFTmagBuff[i];
         }
    }
    // Ѱ�ҳ����ȴ�������ź� Min_Max 0.1 ����Ƶ���ź�
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
    // ����һ�����еĽϴ���ȵĲ����ź�
    // ���������ɢ����Ҷ�任�������㷨������߾���
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

    // ������������֮ǰ����ıȽϾ�׼��Ƶ����Ϣ��������һ�·�������λ
    for(i=0;i<k;i++)
    {

    }
}





































// ���� rfft ��صı����������Ҹ����Ƿ����ַ
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

