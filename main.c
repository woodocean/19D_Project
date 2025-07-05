// ʹ�� FFT �㷨ǰ�����ȵ� F28379D_my_rfft.h �ļ���
// �޸Ĳ��� RFFT_STAGES ���������ȡֵӦ�ò�С��4��������9
// ���������Ӧ�Ĳ���������� pow(2,RFFT_STAGES+1)

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


    // ˵����һ��Ӧ�����������ѭ��������������ɺ�ֹͣ����
    // ˼·���£��������жϺ����н����������� if �жϽ����޸�
    //          ������ȡ���жϣ����жϱ���ȥ������λ�ã�����
    //          �� PIE �� ADC �����Ĳ���ȥ��
    // ���ڲ��õķ�������������������ݺ��Զ��ر��� EPWM
    // �Ӷ�ʵ�ֹر��ж�
    while(1){
        StartEPWM1(TB_COUNT_UP);
        Wait_ADC_ENDING();

        RFFT_adc_f32(hnd_rfft_adc);   // Calculate real FFT (12-bit ADC input)
        flagInputReady = 0;           // Reset the flag

        // TMU0 ��ʾ����ĳ�ּ�������ļ�����
        // ���û�еĻ���ʹ�� RFFT_f32_mag() �Ⱥ���
        RFFT_f32_mag_TMU0(hnd_rfft);        //Calculate magnitude
        RFFT_f32_phase_TMU0(hnd_rfft);      //Calculate phase

        freq = Caculate_Freq();

        ESTOP0;
    }
}

// End of main



