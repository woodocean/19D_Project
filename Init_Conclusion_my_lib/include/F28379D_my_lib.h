/*
 * F28379D_my_lib.h
 *
 *  Created on: 2024��7��11��
 *      Author: Lenovo
 */

#ifndef INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_LIB_H_
#define INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_LIB_H_


// �μ� 24 ��ʡ����ѧ������ƾ�����Ҫ�õ��Ĳ���
#define CPU_FRQ_200MHZ          1
#define ADC_SAMPLING_FREQ       1040284.3L  // ���ۼ����ֵλ1000000L�����ȡֵ��ʵ��������
#define EPWM_HSPCLKDIV          1           //EPWM_CLOCK is SYSCLK/(2*2)



#include "F28379D_my_adc.h"
#include "F28379D_my_epwm.h"
#include "F28379D_my_pie.h"
#include "F28379D_my_clocks.h"
#include "F28379D_my_flash.h"
#include "F28379D_my_sci.h"


#endif /* INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_LIB_H_ */
