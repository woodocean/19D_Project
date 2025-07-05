/*
 * F28379D_my_epwm.c
 *
 *  Created on: 2024��7��11��
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#include "F28379D_my_epwm.h"


//
// ConfigureEPWM1()
//   ��������Ĺ��������� epwm1 ��Ӧ�Ĳ���
//   ��Ҫ˵������������������� epwm1 û�����������Ĵ����Ĺ���
//   ����˵����
//      1�� period �ò��������� epwm1 ����������һ�ֵ�ʱ�������޸��������޸� epwm1 ������Ƶ��
//          Ȼ���޸����õ���Ƶ�����м��޵ģ���Ϊ�ڲ����ж��Լ�����������������Ҫʱ�䣨���˲²⣩
//      2�� compareA �ò��������� epwm1 �������ǵ����ٵ�ʱ��ʼһ�ִ��������������������
//          ʵ�ʶ���Ƶ��û��Ӱ�죬������ֱ�Ӱ����õ�����״̬������ period С 1 ���պ�����ɹ���
//

void ConfigureEPWM1(Uint16 period)
{
    EALLOW;

    EPwm1Regs.ETSEL.bit.SOCAEN    = 0;    // Disable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL    = 4;   // Select SOC on up-count
    EPwm1Regs.ETPS.bit.SOCAPRD = 0b11;       // Generate pulse on 1st event

    // ���������п������� epwm ��Ƶ�ʣ�����Ӧ��ע�����
    // �ڰ������õ� adc ������ʱ�򣬷���
    // ����Ƶ��������ʵ���ɵ��ڵ�Ƶ�ʺ�С��
    // �伫�޲�������� 0x0010 �� 0x0008 ����ط�
    // ���˲²�����ΪƵ��̫�ߵĻ�����������һЩ����ز�����
    // ��Щ�������վ����˼��޵Ĳ���Ƶ��
    EPwm1Regs.CMPA.bit.CMPA = period - 1;     // Set compare A value to 8 counts
    EPwm1Regs.TBPRD = period;             // Set period to 16 counts
    EPwm1Regs.TBCTL.bit.CTRMODE = 3;      // freeze counter
    EDIS;
}

//
// StartEPWM1():
// ����˵���� �ú������������ú� epwm1 ��Ӧ����ز������ epwm1 �������������ʽ
// ����˵���� count_mode
//     �ò���Ӱ���� epwm �ļ�����ʽ��
//     ��ȡ��ֵ�У� TB_COUNT_UP �� TB_COUNT_DOWN ��
//              TB_COUNT_UPDOWN �� TB_FREEZE
//
void StartEPWM1(Uint16 count_mode)
{
    EALLOW;

    // ʹ�� SOCA �� epwm1 ģ��� A �� (GROUP A) �� Start of Conversion �¼�
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;

    // ����/�ر� epwm1 ģ��ļ���ģʽ
    EPwm1Regs.TBCTL.bit.CTRMODE = count_mode;

    EDIS;
}

//
// StopEPWM1()
// �������ܣ�ֹͣ EPWM1 �Ĺ���
// ����˵��������������ǹر� EPWM1 �ļ�����ת���������Բ���Ҫ����
//
void StopEPWM1(void)
{
    EALLOW;
    EPwm1Regs.ETSEL.bit.SOCAEN = 0;  //disable SOCA
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE; //freeze counter
    EDIS;
}
// �������������ʹ�ô��ɣ���Ϊû���õ���
// ��֮��� DAC �������ʱ���������
//void ConfigureEPWM2(Uint16 period)
//{
//    EALLOW;
//
//    EPwm2Regs.ETSEL.bit.SOCAEN    = 0;    // Disable SOC on A group
//    EPwm2Regs.ETSEL.bit.SOCASEL    = 4;   // Select SOC on up-count
//    EPwm2Regs.ETPS.bit.SOCAPRD = 1;       // Generate pulse on 1st event
//
//    // ���������п������� epwm ��Ƶ�ʣ�����Ӧ��ע�����
//    // �ڰ������õ� adc ������ʱ�򣬷���
//    // ����Ƶ��������ʵ���ɵ��ڵ�Ƶ�ʺ�С��
//    // �伫�޲�������� 0x0010 �� 0x0008 ����ط�
//    // ���˲²�����ΪƵ��̫�ߵĻ�����������һЩ����ز�����
//    // ��Щ�������վ����˼��޵Ĳ���Ƶ��
//    EPwm2Regs.CMPA.bit.CMPA = period - 1;     // Set compare A value to 8 counts
//    EPwm2Regs.TBPRD = period;             // Set period to 16 counts
//    EPwm2Regs.TBCTL.bit.CTRMODE = 3;      // freeze counter
//    EDIS;
//}
