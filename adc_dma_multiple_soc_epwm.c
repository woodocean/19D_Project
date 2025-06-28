#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "gpio.h"

//
// �궨��
//
#define TBCLK                   100000000
#define RESULTS_BUFFER_SIZE     256
#define EX_ADC_RESOLUTION       12
#define DISCARD                 5
//
//ȫ�ֱ���
//
#pragma DATA_SECTION(adcAResults, "ramgs0");
#pragma DATA_SECTION(adcBResults, "ramgs0");
uint16_t adcAResults[RESULTS_BUFFER_SIZE + DISCARD];   // �����·����� �� ��·�������ڲ�������
uint16_t adcBResults[RESULTS_BUFFER_SIZE + DISCARD];  //  �����·����� �� ��·�������ڲ�������
uint16_t index;                              // �������
volatile uint16_t bufferFull;                // ����־λ
//
// ��������
void initEPWM(void);    //ePWM��������syscfg����Ƶ�ʣ�����ժ�����̵ĺ���
void SetSamplingRate(uint32_t freq);
void initializeDMA(void);
void configureDMAChannels(void);
void INTERRUPT_init();
__interrupt void dmach1ISR(void);
void Filt_avg(uint16_t* data,uint16_t DATASIZE);
void main(void)
{
    //
    // ��ʼ��
    //
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();

    Board_init();
    INTERRUPT_init();
    initializeDMA();
    configureDMAChannels();
    initEPWM();

    // ��ʼ������
    for(index = 0; index < RESULTS_BUFFER_SIZE; index++)
    {
        adcAResults[index] = 0;
        adcBResults[index] = 0;
    }
    index = 0;
    bufferFull = 0;

    //
    // ȫ���ж�ʹ�ܺ�ʵʱ�ж�ʹ��
    //
    EINT;
    ERTM;

    while(1)
    {

        /*1.�˴���������
        *
        * */


        /*2.�˴�ADC���� */

        /*����1*/
        //����DMA
        DMA_startChannel(DMA_CH1_BASE);
        DMA_startChannel(DMA_CH2_BASE);
        //����ePWM��SOCA������ͬʱҲ����ePWM������
        bufferFull = 0;     // Clear the buffer full flag
        SetSamplingRate(800000);
        EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);


        //�ȴ��������
        while(bufferFull == 0)
        {
        }
        // ֹͣePWM��SOC������ֹͣePWM���������Ӷ�ֹͣ����SOC0�Ĳ���
        EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);

        /*2.1.�˴��������ݷ���
        *
        * */
        Filt_avg(adcAResults,RESULTS_BUFFER_SIZE + DISCARD);
        Filt_avg(adcBResults,RESULTS_BUFFER_SIZE + DISCARD);

        /*����2*/
        //����DMA
        DMA_startChannel(DMA_CH1_BASE);
        DMA_startChannel(DMA_CH2_BASE);

        bufferFull = 0;     // Clear the buffer full flag
        SetSamplingRate(2500000);
        EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);

        while(bufferFull == 0)
        {
        }
        // ֹͣePWM��SOC������ֹͣePWM���������Ӷ�ֹͣ����SOC1�Ĳ���
        EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);

        /*2.2.�˴��������ݷ���
         *
         * */
        Filt_avg(adcAResults,RESULTS_BUFFER_SIZE + DISCARD);
        Filt_avg(adcBResults,RESULTS_BUFFER_SIZE + DISCARD);

        /*3.�˴�������Ļ��ʾ
                 *
                 * */

        ESTOP0;
    }
}

//ePWM���ã���Ҫ��Ƶ������
void initEPWM(void)
{
    GPIO_setPinConfig(GPIO_0_EPWM1A);

    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);


    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //�����������ePWM������������Ϊ200����TBCLK��������COMPA��ֵΪ100
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

    freq = TBCLK/freq;

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
    DMA_configAddresses(DMA_CH1_BASE, (uint16_t *)&adcAResults,
                        (uint16_t *)ADCARESULT_BASE);

    //
    // Perform enough 16-word bursts to fill the results buffer. Data will be
    // transferred 16 bits at a time hence the address steps below.
    //
    DMA_configBurst(DMA_CH1_BASE, 1, 0, 0);
    DMA_configTransfer(DMA_CH1_BASE, (RESULTS_BUFFER_SIZE),0, 1);
    DMA_configMode(DMA_CH1_BASE, DMA_TRIGGER_ADCA1,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH1_BASE);
    DMA_disableOverrunInterrupt(DMA_CH1_BASE);
    DMA_setInterruptMode(DMA_CH1_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH1_BASE);

   //
    // DMA channel 2 set up for ADCB
    //
    DMA_configAddresses(DMA_CH2_BASE, (uint16_t *)&adcBResults,
                        (uint16_t *)ADCCRESULT_BASE);

    //
    // Perform enough 16-word bursts to fill the results buffer. Data will be
    // transferred 32 bits at a time hence the address steps below.
    //
    DMA_configBurst(DMA_CH2_BASE, 1, 0, 0);
    DMA_configTransfer(DMA_CH2_BASE, (RESULTS_BUFFER_SIZE), 0, 1);
    DMA_configMode(DMA_CH2_BASE, DMA_TRIGGER_ADCA1,
                   (DMA_CFG_ONESHOT_DISABLE | DMA_CFG_CONTINUOUS_DISABLE |
                    DMA_CFG_SIZE_16BIT));

    DMA_enableTrigger(DMA_CH2_BASE);
    DMA_disableOverrunInterrupt(DMA_CH2_BASE);
    DMA_setInterruptMode(DMA_CH2_BASE, DMA_INT_AT_END);
    DMA_enableInterrupt(DMA_CH2_BASE);
}
void INTERRUPT_init(){
    Interrupt_register(INT_DMA_CH1, &dmach1ISR);
    Interrupt_enable(INT_DMA_CH1);
}
__interrupt void dmach1ISR(void){
    bufferFull = 1;
    //
    // Acknowledge interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP7);
}
void Filt_avg(uint16_t* data,uint16_t DATASIZE){
    uint16_t i;
    for(i=1;i<DATASIZE;i+=2){
        data[i] = (data[i-1] + data[i+1])/2;
    }
    for(i=0;i<DATASIZE - DISCARD;i++){
        data[i] = data[i + DISCARD];
    }
}
