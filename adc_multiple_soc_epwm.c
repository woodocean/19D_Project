#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// �궨��
//
#define TBCLK                   100000000
#define RESULTS_BUFFER_SIZE     256
#define EX_ADC_RESOLUTION       12
#define DISCARD                 3
//
//ȫ�ֱ���
//
uint16_t adcAResults[RESULTS_BUFFER_SIZE];   // �����·�����
uint16_t adcBResults[RESULTS_BUFFER_SIZE];  //  �����·����ˣ�������˲�����Ҫͬ��
uint16_t adcAResults1[RESULTS_BUFFER_SIZE]; //  ���������ڲ������������·����ˣ���adcBResults1����Ҫͬ��
uint16_t adcBResults1[RESULTS_BUFFER_SIZE];//   ���������ڲ������������·�����
uint16_t index;                              // �������
volatile uint16_t bufferFull;                // ����־λ
volatile uint16_t discard;                   //������־λ������һ��ʼ�������쳣ֵ
//
// ��������
void initEPWM(void);    //ePWM��������syscfg����Ƶ�ʣ�����ժ�����̵ĺ���
void SetSamplingRate(uint32_t freq);

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
    ADC_init();
    INTERRUPT_init();
    initEPWM();

    // ��ʼ������
    for(index = 0; index < RESULTS_BUFFER_SIZE; index++)
    {
        adcAResults[index] = 0;
        adcBResults[index] = 0;
        adcAResults1[index] = 0;
        adcBResults1[index] = 0;
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
        //
        //����ePWM��SOCA������ͬʱҲ����ePWM������
        //
        bufferFull = 0;     // Clear the buffer full flag
        SetSamplingRate(750000);
        EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);


        while(bufferFull == 0)
        {
        }
        // ֹͣePWM��SOC������ֹͣePWM������
        EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);

        /*3.�˴��������ݷ���
         *
         * */

        /*4.�˴�������Ļ��ʾ
                 *
                 * */

        ESTOP0;
    }
}

//ePWM���ã���Ҫ��Ƶ������
void initEPWM(void)
{
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);


    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //�����������ePWM������������Ϊ200����TBCLK��������COMPA��ֵΪ100
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 100);
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

//ADC�жϺ���
__interrupt void ADC_ISR(void)
{
    //��־λ����--�����Ѵ���--��д������
    if(0 == bufferFull){

            adcAResults[index] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
            adcBResults[index] = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);
            adcAResults1[index] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
            adcBResults1[index] = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER1);
            index ++;

            if((DISCARD <= index)&&(0 == discard)){
                index = 0;
                discard = 1;
            }

            //����������־λ�ø�--���ݴ�����
            if(RESULTS_BUFFER_SIZE <= index)
            {
                index = 0;
                bufferFull = 1;
                discard = 0;
            }
    }

    //
    // ����жϱ�־λ
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    // ����ж����
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }

    //����ж�Ӧ�����־λ����ǰ�ж��Ѵ�����ɣ��������ͬ�������жϴ���
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);


}
