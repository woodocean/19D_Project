#include "fpu_rfft.h"            // Main include file
#include "math.h"
#include "examples_setup.h"
#include "driverlib.h"
#include "device.h"
#include "board.h"
//宏定义
#define RFFT_STAGES     9
#define RFFT_SIZE       (1 << RFFT_STAGES) 
#define F_PER_SAMPLE    (ADC_SAMPLING_FREQ/(float)RFFT_SIZE)
#define EPSILON         0.1

#define TBCLK           100000000
//全局变量以及数组分配内存
uint16_t RFFTin1Buff[2*RFFT_SIZE];
uint16_t RFFTin2Buff[2*RFFT_SIZE];
float RFFTF32Coef[RFFT_SIZE];
float RFFToutBuff[RFFT_SIZE];
float RFFTmagBuff[RFFT_SIZE/2+1];
#pragma DATA_SECTION(RFFTin1Buff,"RFFTdata1")
#pragma DATA_SECTION(RFFTmagBuff,"RFFTdata2")
#pragma DATA_SECTION(RFFToutBuff,"RFFTdata3")
#pragma DATA_SECTION(RFFTF32Coef,"RFFTdata4")
#pragma DATA_SECTION(RFFTin2Buff,"RFFTdata5")

volatile uint16_t bufferFull;                // 满标志位


//结构体变量
RFFT_ADC_F32_STRUCT rfft_adc;                           //rfft输入结构体    
RFFT_ADC_F32_STRUCT_Handle hnd_rfft_adc = &rfft_adc;    //rfft输入结构体地址
RFFT_F32_STRUCT rfft;                                   //rfft运算结构体
RFFT_F32_STRUCT_Handle hnd_rfft = &rfft;                //rfft运算结构体地址
volatile uint16_t flagInputReady = 0;
volatile uint16_t sampleIndex = 0;

__interrupt void dmach1ISR(void);
void initEPWM(void);    //ePWM好像不能用syscfg配置频率，所以摘了例程的函数
void SetSamplingRate(uint32_t freq);
void initializeDMA(void);
void configureDMAChannels(void);


void main(void)
{

    uint16_t i, j;
    float freq = 0.0;

//预定义FLASH则将FLASH中的函数加载到RAM，这样可以将程序烧录到FLASH的同时（断电保存），将FFT运行程序放到RAM运行（更快）
#ifdef FLASH
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
    memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
            (uint32_t)&RamfuncsLoadSize );
    FPU_initFlash();
#endif //FLASH

    // 初始化
    // //
     Device_init();
    // Device_initGPIO();
    // Interrupt_initModule();
    // Interrupt_initVectorTable();
    /*初始化时钟、中断、ADC、EPWM*/
    //
    Board_init();
    Interrupt_register(INT_DMA_CH1, &dmach1ISR);
    Interrupt_enable(INT_DMA_CH1);
    initializeDMA();
    configureDMAChannels();
    initEPWM();

    //
    // 全局中断使能和实时中断使能
    //
    EINT;
    ERTM;

    
    //分配结构体变量，以及变量初始化
    hnd_rfft_adc->Tail = &(hnd_rfft->OutBuf); 
    hnd_rfft->FFTSize   = RFFT_SIZE;       //FFT size
    hnd_rfft->FFTStages = RFFT_STAGES;     //FFT stages
    hnd_rfft_adc->InBuf = &RFFTin1Buff[0]; //Input buffer (12-bit ADC) input
    hnd_rfft->OutBuf    = &RFFToutBuff[0]; //Output buffer
    hnd_rfft->CosSinBuf = &RFFTF32Coef[0]; //Twiddle factor 
    hnd_rfft->MagBuf    = &RFFTmagBuff[0]; //Magnitude output buffer
    RFFT_f32_sincostable(hnd_rfft);        //Calculate twiddle factor
    for (i=0; i < RFFT_SIZE; i++){
        RFFToutBuff[i] = 0;                //Clean up output buffer
    }                                                                   
    for (i=0; i < RFFT_SIZE/2; i++){       
        RFFTmagBuff[i] = 0;                //Clean up magnitude buffer
    }   


    while(1){
         /*2.此处ADC采样 */

        /*采样1*/
       
        //开启ePWM的SOCA触发，同时也开启ePWM计数器
        bufferFull = 0;     // Clear the buffer full flag
        SetSamplingRate(8000000);
        EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

         //开启DMA
        DMA_startChannel(DMA_CH1_BASE);
        DMA_startChannel(DMA_CH2_BASE);
        //等待采样完成
        while(bufferFull == 0)
        {
        }
        // 停止ePWM的SOC触发，停止ePWM计数器，从而停止两个SOC0的采样
        EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
        bufferFull =0;     //标志位复位

        /*2.1.此处进行数据分析 */
#ifdef __TMS320C28XX_TMU__ //defined when --tmu_support=tmu0 in the project 
                           // properties
        RFFT_f32_mag_TMU0(hnd_rfft);        //Calculate magnitude
#else
        RFFT_f32_mag(hnd_rfft);             //Calculate magnitude
#endif //__TMS320C28XX_TMU__

        j = 1;
        freq = RFFTmagBuff[1];
        for(i=2;i<RFFT_SIZE/2+1;i++){
        //Looking for the maximum component of frequency spectrum
            if(RFFTmagBuff[i] > freq){
                j = i;
                freq = RFFTmagBuff[i];
            }
        }
        freq = F_PER_SAMPLE * (float)j;     
    }
}

//ePWM配置，主要是频率配置
void initEPWM(void)
{
    GPIO_setPinConfig(GPIO_0_EPWM1A);

    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);


    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //这两句表明，ePWM波计数器周期为200（个TBCLK），设置COMPA的值为100
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 100);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM1_BASE,
                                      EPWM_AQ_OUTPUT_A,
                                      EPWM_AQ_OUTPUT_HIGH,
                                      EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 199);


    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);
    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);

}

void SetSamplingRate(uint32_t freq){

    freq = TBCLK/(freq);

    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, freq/2);
    EPWM_setTimeBasePeriod(EPWM1_BASE, freq -1);
}


//
// initializeDMA - Initialize DMA through hard reset
//
void initializeDMA(void)
{
    //
    // Perform a hard reset on DMA
    //
    DMA_initController();

    //
    // Allow DMA to run free on emulation suspend
    //
    DMA_setEmulationMode(DMA_EMULATION_FREE_RUN);
}

void configureDMAChannels(void)
{
    //
    // DMA channel 1 set up for ADCA
    //
    DMA_configAddresses(DMA_CH1_BASE, (uint16_t *)&RFFTin1Buff,
                        (uint16_t *)ADCARESULT_BASE);

    //
    // Perform enough 16-word bursts to fill the results buffer. Data will be
    // transferred 16 bits at a time hence the address steps below.
    //
    DMA_configBurst(DMA_CH1_BASE, 1, 0, 0);
    DMA_configTransfer(DMA_CH1_BASE, 2*RFFT_SIZE,0, 1);
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_ADCA2,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH1_BASE);
    DMA_disableOverrunInterrupt(DMA_CH1_BASE);
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH1_BASE);

   //
    // DMA channel 2 set up for ADCB
    //
    DMA_configAddresses(DMA_CH2_BASE, (uint16_t *)&RFFTin2Buff,
                        (uint16_t *)ADCBRESULT_BASE);

    //
    // Perform enough 16-word bursts to fill the results buffer. Data will be
    // transferred 32 bits at a time hence the address steps below.
    //
    DMA_configBurst(DMA_CH2_BASE, 1, 0, 0);
    DMA_configTransfer(DMA_CH2_BASE, 2*RFFT_SIZE, 0, 1);
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_ADCA1,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH2_BASE);
    DMA_disableOverrunInterrupt(DMA_CH2_BASE);
    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH2_BASE);
}

__interrupt void dmach1ISR(void){
    bufferFull = 1;
    //
    // Acknowledge interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}
