/*
 * F28379D_my_adc.h
 *
 *  Created on: 2024-7-10
 *      Author: Lenovo
 */
/*
 * ��������Ӧ�� C �ļ��У��ҽ��Ἧ�� adc �����Ĵ������á�Ƶ�����á��������ݽ���洢�ռ�������õ�
 */

#include "F28x_Project.h"


#ifndef INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_ADC_H_
#define INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_ADC_H_


extern void ConfigureADC(Uint16 adc);
extern void SetupADCAEpwm1(Uint16 channel);
extern void SetupADCBEpwm1(Uint16 channel);

extern void Wait_ADC_ENDING(void);

extern interrupt void adcaIsr();

#endif /* INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_ADC_H_ */
