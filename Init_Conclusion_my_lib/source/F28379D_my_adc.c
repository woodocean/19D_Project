/*
 * F28379D_my_adc.c
 *
 *  Created on: 2024年7月10日
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
//   这个函数的功能是配置需要的 adc 采样对应的参数。
//   设置的参数有： Prescale 、 Resolution 、
//                Signalmode 、 Intpulsepos 、 Adcpwdnz
//   参数说明：
//      1、 Prescale ：这个设置的是 adc 采样的时间分辨率
//              它越大的话，采样的时间越短，最终数据的精度越高。
//              此处直接控制为尽可能的大，设置为八分之一的采样时间
//      2、 Resolution ：这个设置的是 adc 采样的数据精度
//              它一共有两个选择，一个是 12 位数据，一个是 16 位数据
//              可以配置的参数有：
//              ADC_RESOLUTION_12BIT 、 ADC_RESOLUTION_16BIT
//              经过认真考虑，认为我们可能大概率是仅仅会用到 12 位的，如果需要再改
//      3、 Signalmode ：这个设置的是 adc 采样的通道使用方式
//              它也一共仅有两个选择，一个是单端 adc 采样（电压采样）
//              另一个是双端 adc 采样（差分电压采样，用于测量高电压）
//              可以配置的参数有：
//              ADC_SIGNALMODE_SINGLE 、 ADC_SIGNALMODE_DIFFERENTIAL
//              经过认真考虑，认为我们大概率是不会使用到差分电压测量，默认单端
//      4、 Intpulsepos ： 这个设置的是数据完成采样后是否设置中断
//              在这个函数里面，我们默认需要中断来提示可以开始处理数据。
//              在中断设计中，可以借鉴 flag 的方式标志
//              在数据处理不是那么得紧迫下，我们可以设置一个标志位表示可以开始处理
//              然后在主函数里面加一个观测即可。
//              如果另外考虑了低功耗的情况下，则忽略上述所说
//      5、 Adcpwdnz ： 这个设置的是 adc 采样功能的能量供给状态
//              在这个函数里，直接设置为开启能量供应
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
//   这个函数的功能是配置 adca 触发是由 Epwm1 完成
//   经过修改
//   有关的参数：  Resolution 、 channel
//   参数说明：
//      1、 Resolution ：这个设置的是 adc 采样的数据精度
//              它一共有两个选择，一个是 12 位数据，一个是 16 位数据
//              可以配置的参数有：
//              ADC_RESOLUTION_12BIT 、 ADC_RESOLUTION_16BIT
//              经过认真考虑，认为我们可能大概率是仅仅会用到 12 位的，如果需要再改
//              而对于之后的采样时间 acqps 设置，这里要说明的是，
//              对于 12 位数据采样，将它设为 14 ，而对于 16 位数据采样，则要把它设置为 63 即 320ns
//      3、 channel ： 这个设置的是 adc 采样的端口，是哪一个通道
//              可以选择的通道有
//              ADC_CHANNEL_0 一直到 ADC_CHANNEL_15
//              对应关系：
//              ADC_CHANNEL_i  ----  ADCINi
//              而对于差分电压测量的话，一般来说它将会测量
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

    // 设置了中断函数相关的内容
    //Map ISR functions
    EALLOW;
    PieVectTable.ADCA1_INT = &adcaIsr; //function for ADCA interrupt 1
    EDIS;


    // 开启1.1对应的中断
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

    //如果 ADCA 与 ADCB 共用一个触发源中断的话，下面这两行可以不用配置。
    //AdcbRegs.ADCINTSEL1N2.bit.INT1SEL = 0;      //end of SOC0 will set INT1 flag
    //AdcbRegs.ADCINTSEL1N2.bit.INT1E = 1;        //enable INT1 flag
    //AdcbRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;      //make sure INT1 flag is cleared
    EDIS;
}



//
// 这个函数代替了延时等待采样结果的功能
// 也就是把 while 循环给替代了
// 不过为了避免程序跑飞，增加了采样不足也会直接停下的命令
//
void Wait_ADC_ENDING(void)
{
//    long long int count=RFFT_SIZE*18*512;
    while(flagInputReady == 0)
    {
    }
}


// 将中断函数设置到这里可以更好的实现版本修改
// 或者说简化主函数，突出中心问题
// 在开启一次之后，它将会自动关闭中断内容
// 方式是关闭触发 ADC 中断的 epwm
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




