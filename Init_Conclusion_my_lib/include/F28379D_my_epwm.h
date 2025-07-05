/*
 * F28379D_my_epwm.h
 *
 *  Created on: 2024��7��11��
 *      Author: Lenovo
 */
/*
 * ��������Ӧ�� C �ļ��У��ҽ��Ἧ�� epwm ��Ƶ�����á�ռ�ձ����á�����ܽſ��Ƶȵ�
 * ����˵�������ڹ���רһ�����ǣ���Ȼ epwm ����ʵ�ֺܶ๦�ܣ�����ͨ������ռ�ձ�������������ʵȵ�
 * ���Ǳ������⽫��� EPWM1 �� EPWM2 �� EPWM3 �� EPWM4 ��ֻ��������Դ������ר�� ADC �� DAC ģ��Ĵ���Դ
 */

#include "F28x_Project.h"


#ifndef INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_EPWM_H_
#define INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_EPWM_H_




extern void ConfigureEPWM1(Uint16 period);
//extern void ConfigureEPWM2(Uint16 period);

extern void StartEPWM1(Uint16 count_mode);
extern void StopEPWM1(void);



#endif /* INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_EPWM_H_ */
