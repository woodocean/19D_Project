/*
 * BlueTooth_HC_06.h
 *
 *  Created on: 2024��7��26��
 *      Author: Lenovo
 */

#include "F28x_Project.h"

#ifndef INIT_CONCLUSION_MY_LIB_PERIPHERAL_CONTROL_BLUETOOTH_HC_06_H_
#define INIT_CONCLUSION_MY_LIB_PERIPHERAL_CONTROL_BLUETOOTH_HC_06_H_


// ��ȷ����֮����������ֻ�֮�䴫���
// ���ݸ�ʽ��Ӧ��������ֵ��ȷ����
// ������ȫ������ȷ������
// �������ı���������ʵ���ǲ�����ȫȷ����
// ��Ҫ���ݾ����Ҫ���������޸�
// ���ڽ���ֻ����һ��ʾ��
// ������ȫ�п�����֮���ʱ����Ҫǿתһ��
// float ���͵�����Ϊ�ĸ� unsigned char ���͵�����
#define SENDNUM         5
#define RECEIVENUM     1
struct HC_06_data
{
    unsigned char senddata[SENDNUM];
    unsigned char sendnum;
    unsigned char receivedata[RECEIVENUM + 3];
    unsigned char adjustdata[RECEIVENUM + 1];
    unsigned char receivenum;
};
extern struct HC_06_data bluetooth_d;


extern void BlueTooth_send(void);
extern interrupt void scibRxFifoIsr(void);


extern void HC_06_Init(void);


#endif /* INIT_CONCLUSION_MY_LIB_PERIPHERAL_CONTROL_BLUETOOTH_HC_06_H_ */
