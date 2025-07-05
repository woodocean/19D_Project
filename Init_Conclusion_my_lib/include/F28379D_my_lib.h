/*
 * F28379D_my_lib.h
 *
 *  Created on: 2024年7月11日
 *      Author: Lenovo
 */

#ifndef INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_LIB_H_
#define INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_LIB_H_


// 参加 24 年省级大学生点设计竞赛需要用到的参数
#define CPU_FRQ_200MHZ          1
#define ADC_SAMPLING_FREQ       1040284.3L  // 理论计算的值位1000000L，这个取值是实验测出来的
#define EPWM_HSPCLKDIV          1           //EPWM_CLOCK is SYSCLK/(2*2)



#include "F28379D_my_adc.h"
#include "F28379D_my_epwm.h"
#include "F28379D_my_pie.h"
#include "F28379D_my_clocks.h"
#include "F28379D_my_flash.h"
#include "F28379D_my_sci.h"


#endif /* INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_LIB_H_ */
