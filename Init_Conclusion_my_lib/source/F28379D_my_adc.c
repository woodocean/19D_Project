/*
 * F28379D_my_adc.c
 *
 *  Created on: 2024��7��10��
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"


#include "F28379D_my_adc.h"
#include "F28379D_my_rfft.h"

extern volatile uint16_t flagInputReady;
extern volatile uint16_t sampleIndex;

//
// ConfigureADC()
//   ��������Ĺ�����������Ҫ�� adc ������Ӧ�Ĳ�����
//   ���õĲ����У� Prescale �� Resolution ��
//                Signalmode �� Intpulsepos �� Adcpwdnz
//   ����˵����
//      1�� Prescale ��������õ��� adc ������ʱ��ֱ���
//              ��Խ��Ļ���������ʱ��Խ�̣��������ݵľ���Խ�ߡ�
//              �˴�ֱ�ӿ���Ϊ�����ܵĴ�����Ϊ�˷�֮һ�Ĳ���ʱ��
//      2�� Resolution ��������õ��� adc ���������ݾ���
//              ��һ��������ѡ��һ���� 12 λ���ݣ�һ���� 16 λ����
//              �������õĲ����У�
//              ADC_RESOLUTION_12BIT �� ADC_RESOLUTION_16BIT
//              �������濼�ǣ���Ϊ���ǿ��ܴ�����ǽ������õ� 12 λ�ģ������Ҫ�ٸ�
//      3�� Signalmode ��������õ��� adc ������ͨ��ʹ�÷�ʽ
//              ��Ҳһ����������ѡ��һ���ǵ��� adc ��������ѹ������
//              ��һ����˫�� adc ��������ֵ�ѹ���������ڲ����ߵ�ѹ��
//              �������õĲ����У�
//              ADC_SIGNALMODE_SINGLE �� ADC_SIGNALMODE_DIFFERENTIAL
//              �������濼�ǣ���Ϊ���Ǵ�����ǲ���ʹ�õ���ֵ�ѹ������Ĭ�ϵ���
//      4�� Intpulsepos �� ������õ���������ɲ������Ƿ������ж�
//              ������������棬����Ĭ����Ҫ�ж�����ʾ���Կ�ʼ�������ݡ�
//              ���ж�����У����Խ�� flag �ķ�ʽ��־
//              �����ݴ�������ô�ý����£����ǿ�������һ����־λ��ʾ���Կ�ʼ����
//              Ȼ���������������һ���۲⼴�ɡ�
//              ������⿼���˵͹��ĵ�����£������������˵
//      5�� Adcpwdnz �� ������õ��� adc �������ܵ���������״̬
//              ����������ֱ������Ϊ����������Ӧ
//
void ConfigureADC(Uint16 adc)
{
    EALLOW;

    switch(adc)
    {
        case ADC_ADCA:
        {
            AdcaRegs.ADCCTL2.bit.PRESCALE = 0b1110;

            AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

            AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;

            AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;

            break;
        }
        case ADC_ADCB:
        {
            AdcbRegs.ADCCTL2.bit.PRESCALE = 0b1110;

            AdcSetMode(ADC_ADCB, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

            AdcbRegs.ADCCTL1.bit.INTPULSEPOS = 1;

            AdcbRegs.ADCCTL1.bit.ADCPWDNZ = 1;

            break;
        }
        case ADC_ADCC:
        {
            AdccRegs.ADCCTL2.bit.PRESCALE = 0b1110;

            AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

            AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;

            AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;

            break;
        }
        case ADC_ADCD:
        {
            AdcdRegs.ADCCTL2.bit.PRESCALE = 0b1110;

            AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

            AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 1;

            AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;

            break;
        }
        default:
            ESTOP0;
    }

    EDIS;
    DELAY_US(1000);

}



//
// SetupADCAEpwm1()
//   ��������Ĺ��������� adca �������� Epwm1 ���
//   �����޸�
//   �йصĲ�����  Resolution �� channel
//   ����˵����
//      1�� Resolution ��������õ��� adc ���������ݾ���
//              ��һ��������ѡ��һ���� 12 λ���ݣ�һ���� 16 λ����
//              �������õĲ����У�
//              ADC_RESOLUTION_12BIT �� ADC_RESOLUTION_16BIT
//              �������濼�ǣ���Ϊ���ǿ��ܴ�����ǽ������õ� 12 λ�ģ������Ҫ�ٸ�
//              ������֮��Ĳ���ʱ�� acqps ���ã�����Ҫ˵�����ǣ�
//              ���� 12 λ���ݲ�����������Ϊ 14 �������� 16 λ���ݲ�������Ҫ��������Ϊ 63 �� 320ns
//      3�� channel �� ������õ��� adc �����Ķ˿ڣ�����һ��ͨ��
//              ����ѡ���ͨ����
//              ADC_CHANNEL_0 һֱ�� ADC_CHANNEL_15
//              ��Ӧ��ϵ��
//              ADC_CHANNEL_i  ----  ADCINi
//              �����ڲ�ֵ�ѹ�����Ļ���һ����˵���������
//              channel(2i+1) -  channel(2i)
//
void SetupADCAEpwm1( Uint16 channel)
{
    Uint16 acqps = 14; //75ns

    EALLOW;
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = channel;    //SOC0 will convert pin A0
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = acqps;      //sample window is 100 SYSCLK cycles
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 5;        //trigger on ePWM1 SOCA/C

    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0;      //end of SOC0 will set INT1 flag

    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;        //enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      //make sure INT1 flag is cleared
    EDIS;

    // �������жϺ�����ص�����
    //Map ISR functions
    EALLOW;
    PieVectTable.ADCA1_INT = &adcaIsr; //function for ADCA interrupt 1
    EDIS;


    // ����1.1��Ӧ���ж�
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;
    IER |= M_INT1;
}
void SetupADCBEpwm1( Uint16 channel)
{
    Uint16 acqps = 14; //75ns

    EALLOW;
    AdcbRegs.ADCSOC0CTL.bit.CHSEL = channel;
    AdcbRegs.ADCSOC0CTL.bit.ACQPS = acqps;
    AdcbRegs.ADCSOC0CTL.bit.TRIGSEL = 5;        //trigger on ePWM2 SOCA/C

    //��� ADCA �� ADCB ����һ������Դ�жϵĻ������������п��Բ������á�
    //AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 0;      //end of SOC0 will set INT1 flag
    //AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;        //enable INT1 flag
    //AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      //make sure INT1 flag is cleared
    EDIS;
}



//
// ���������������ʱ�ȴ���������Ĺ���
// Ҳ���ǰ� while ѭ���������
// ����Ϊ�˱�������ܷɣ������˲�������Ҳ��ֱ��ͣ�µ�����
//
void Wait_ADC_ENDING(void)
{
//    long long int count=RFFT_SIZE*18*512;
    while(flagInputReady == 0)
    {
    }
}


// ���жϺ������õ�������Ը��õ�ʵ�ְ汾�޸�
// ����˵����������ͻ����������
// �ڿ���һ��֮���������Զ��ر��ж�����
// ��ʽ�ǹرմ��� ADC �жϵ� epwm
//! \brief ADC Interrupt Service Routine
//! The ISR will store each sampled value in the FFT buffer, and
//! raise the flag once the buffer is full
//!
interrupt void adcaIsr()
{
    RFFTin1Buff[sampleIndex++] = AdcaResultRegs.ADCRESULT0;
    if(sampleIndex == (2*RFFT_SIZE - 1) )
    {
        sampleIndex = 0;
        flagInputReady = 1;
        StopEPWM1();
    }

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag

    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}




