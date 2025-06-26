#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// 宏定义
//
#define RESULTS_BUFFER_SIZE     256
#define EX_ADC_RESOLUTION       12
//
//全局变量
//
uint16_t adcAResults[RESULTS_BUFFER_SIZE];   // 待测电路输入端
uint16_t adcBResults[RESULTS_BUFFER_SIZE];  //  待测电路输出端，与输入端测量需要同步
uint16_t adcCResults1[RESULTS_BUFFER_SIZE]; //  测量仪器内部，靠近待测电路输入端，与adcCResults2不需要同步
uint16_t adcCResults2[RESULTS_BUFFER_SIZE];//   测量仪器内部，靠近待测电路输出端
uint16_t index;                              // 数组序号
volatile uint16_t bufferFull;                // 满标志位
//
// 函数声明
void initEPWM(void);    //ePWM好像不能用syscfg配置频率，所以摘了例程的函数


void main(void)
{
    //
    // 初始化
    //
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();

    Board_init();
    ADC_init();
    INTERRUPT_init();
    initEPWM();

    // 初始化数组
    for(index = 0; index < RESULTS_BUFFER_SIZE; index++)
    {
        adcAResults[index] = 0;
        adcBResults[index] = 0;
        adcCResults1[index] = 0;
        adcCResults2[index] = 0;
    }
    index = 0;
    bufferFull = 0;

    //
    // 全局中断使能和实时中断使能
    //
    EINT;
    ERTM;

    while(1)
    {

        /*1.此处发生波形
        *
        * */


        /*2.此处ADC采样 */
        //
        //开启ePWM的SOCA触发，同时也开启ePWM计数器
        //
        bufferFull = 0;     // Clear the buffer full flag
        EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_UP);


        while(bufferFull == 0)
        {
        }
        // 停止ePWM的SOC触发，停止ePWM计数器
        EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
        EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);

        /*3.此处进行数据分析
         *
         * */

        /*4.此处进行屏幕显示
                 *
                 * */

        ESTOP0;
    }
}

//ePWM配置，主要是频率配置
void initEPWM(void)
{
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM1_BASE, EPWM_SOC_A);


    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_U_CMPA);
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, 1);

    //这两句表明，ePWM波计数器周期为200（个TBCLK），设置COMPA的值为100
    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, 100);
    EPWM_setTimeBasePeriod(EPWM1_BASE, 199);


    EPWM_setClockPrescaler(EPWM1_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);


    EPWM_setTimeBaseCounterMode(EPWM1_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
}


//ADC中断函数
__interrupt void ADC_ISR(void)
{
    //标志位清零--数据已处理--才写入数组
    if(0 == bufferFull){

            adcAResults[index] = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
            adcBResults[index] = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);
            adcCResults1[index] = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);
            adcCResults2[index] = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1);
            index ++;

            //数组满，标志位置高--数据待处理
            if(RESULTS_BUFFER_SIZE <= index)
            {
                index = 0;
                bufferFull = 1;
            }
    }

    //
    // 清除中断标志位
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    // 检查中断溢出
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }

    //清除中断应答组标志位，当前中断已处理完成，允许后续同组其他中断触发
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);


}
