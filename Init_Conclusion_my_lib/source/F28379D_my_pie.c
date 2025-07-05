/*
 * F28379D_my_pie.cc
 *
 *  Created on: 2024��7��18��
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"


#include "F28379D_my_pie.h"


//
// InitEpie()
// �������ܣ�
//    ��ʼ���ж�����
//    ���ֹ�˿ɱ�־�� CPU �����ж�
//    �������ֹ�����е��ж�
//    ��������������е��ж�ʹ��λ
//    ��������е��жϱ�־λ
//    ��ʼ�������е��ж�������
void InitEpie(void)
{
    DINT;               //Globally disable maskable CPU interrupts
    InitPieCtrl();      //Clear and disable all PIE interrupts
    IER = 0x0000;       //Individually disable maskable CPU interrupts
    IFR = 0x0000;       //Clear all CPU interrupt flags
    InitPieVectTable(); //Populate PIE interrupt vector table with shell ISRs
}


