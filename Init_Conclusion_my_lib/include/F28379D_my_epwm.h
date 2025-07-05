/*
 * F28379D_my_epwm.h
 *
 *  Created on: 2024年7月11日
 *      Author: Lenovo
 */
/*
 * 在这个与对应的 C 文件中，我将会集成 epwm 的频率设置、占空比设置、输出管脚控制等等
 * 补充说明：出于功能专一化考虑，虽然 epwm 可以实现很多功能，例如通过调节占空比来调节输出功率等等
 * 但是本函数库将会把 EPWM1 、 EPWM2 、 EPWM3 和 EPWM4 都只用作触发源并且是专供 ADC 和 DAC 模块的触发源
 */

#include "F28x_Project.h"


#ifndef INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_EPWM_H_
#define INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_EPWM_H_




extern void ConfigureEPWM1(Uint16 period);
//extern void ConfigureEPWM2(Uint16 period);

extern void StartEPWM1(Uint16 count_mode);
extern void StopEPWM1(void);



#endif /* INIT_CONCLUSION_MY_LIB_INCLUDE_F28379D_MY_EPWM_H_ */
