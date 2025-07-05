/*
 * F28379D_my_pie.cc
 *
 *  Created on: 2024年7月18日
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"


#include "F28379D_my_pie.h"


//
// InitEpie()
// 函数功能：
//    初始化中断内容
//    其禁止了可标志的 CPU 级的中断
//    清除并禁止了所有的中断
//    独立地清除了所有的中断使能位
//    清除了所有的中断标志位
//    初始化了所有的中断向量表
void InitEpie(void)
{
    DINT;               //Globally disable maskable CPU interrupts
    InitPieCtrl();      //Clear and disable all PIE interrupts
    IER = 0x0000;       //Individually disable maskable CPU interrupts
    IFR = 0x0000;       //Clear all CPU interrupt flags
    InitPieVectTable(); //Populate PIE interrupt vector table with shell ISRs
}


