// 使用 FFT 算法前，请先到 F28379D_my_rfft.h 文件中
// 修改参数 RFFT_STAGES 这个参数的取值应该不小于4，不大于9
// 这个参数对应的采样点个数是 pow(2,RFFT_STAGES+1)

#include "F28x_Project.h"

#include "F28379D_my_lib.h"
#include "F28379D_my_fft.h"

#include "my_math_lib.h"
#include "my_PeripheralControl_lib.h"

#include "fpu_rfft.h"            // Main include file
#include "math.h"

struct HC_06_data bluetooth_d;
volatile uint16_t flagInputReady = 0;
volatile uint16_t sampleIndex = 0;


void main(void)
{
    float freq;

#ifdef FLASH
    Init_Flash();
#endif //FLASH

    InitSystemClocks();
    InitEpie();
    InitGpio(); // Skipped for this example

    // Setup ADC-A EPWM1
    ConfigureADC(ADC_ADCA);
    SetupADCAEpwm1(ADC_CHANNEL_0);
    ConfigureEPWM1(0x0145);

    EINT;
    ERTM;

    Init_Rfft_F32_Struct();


    // 说明下一步应该在下面这个循环里面加入采样完成后停止采样
    // 思路如下：可以在中断函数中将样本已满的 if 判断进行修改
    //          在那里取消中断，在中断表上去掉它的位置，或者
    //          将 PIE 中 ADC 采样的部分去掉
    // 现在采用的方法是在填满输入的数据后，自动关闭了 EPWM
    // 从而实现关闭中断
    while(1){
        StartEPWM1(TB_COUNT_UP);
        Wait_ADC_ENDING();

        RFFT_adc_f32(hnd_rfft_adc);   // Calculate real FFT (12-bit ADC input)
        flagInputReady = 0;           // Reset the flag

        // TMU0 表示存在某种加速运算的加速器
        // 如果没有的话请使用 RFFT_f32_mag() 等函数
        RFFT_f32_mag_TMU0(hnd_rfft);        //Calculate magnitude
        RFFT_f32_phase_TMU0(hnd_rfft);      //Calculate phase

        freq = Caculate_Freq();

        ESTOP0;
    }
}

// End of main



