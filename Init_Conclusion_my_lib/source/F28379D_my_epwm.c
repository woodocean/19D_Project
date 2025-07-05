/*
 * F28379D_my_epwm.c
 *
 *  Created on: 2024年7月11日
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#include "F28379D_my_epwm.h"


//
// ConfigureEPWM1()
//   这个函数的功能是设置 epwm1 对应的参数
//   需要说明的是这里仅仅配置了 epwm1 没有配置其他寄存器的功能
//   参数说明：
//      1、 period 该参数设置了 epwm1 计数器，记一轮的时钟数，修改它可以修改 epwm1 计数的频率
//          然而修改它得到的频率是有极限的，因为在采样中断以及采样读数过程中需要时间（个人猜测）
//      2、 compareA 该参数设置了 epwm1 计数器记到多少的时候开始一轮触发，但是由于这个参数
//          实际对于频率没有影响，所以我直接把设置到极限状态，仅比 period 小 1 ，刚好能完成功能
//

void ConfigureEPWM1(Uint16 period)
{
    EALLOW;

    EPwm1Regs.ETSEL.bit.SOCAEN    = 0;    // Disable SOC on A group
    EPwm1Regs.ETSEL.bit.SOCASEL    = 4;   // Select SOC on up-count
    EPwm1Regs.ETPS.bit.SOCAPRD = 0b11;       // Generate pulse on 1st event

    // 下面这两行可以设置 epwm 的频率，但是应该注意的是
    // 在把它运用到 adc 采样的时候，发现
    // 随着频率增大，其实它可调节的频率很小。
    // 其极限参数大概在 0x0010 与 0x0008 这个地方
    // 个人猜测是因为频率太高的话，采样中有一些步骤必不可少
    // 这些步骤最终决定了极限的采样频率
    EPwm1Regs.CMPA.bit.CMPA = period - 1;     // Set compare A value to 8 counts
    EPwm1Regs.TBPRD = period;             // Set period to 16 counts
    EPwm1Regs.TBCTL.bit.CTRMODE = 3;      // freeze counter
    EDIS;
}

//
// StartEPWM1():
// 函数说明： 该函数可以在配置好 epwm1 对应的相关参数后打开 epwm1 并设置其计数方式
// 参数说明： count_mode
//     该参数影响了 epwm 的计数方式，
//     可取的值有： TB_COUNT_UP 、 TB_COUNT_DOWN 、
//              TB_COUNT_UPDOWN 、 TB_FREEZE
//
void StartEPWM1(Uint16 count_mode)
{
    EALLOW;

    // 使能 SOCA 即 epwm1 模块的 A 组 (GROUP A) 的 Start of Conversion 事件
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;

    // 设置/关闭 epwm1 模块的计数模式
    EPwm1Regs.TBCTL.bit.CTRMODE = count_mode;

    EDIS;
}

//
// StopEPWM1()
// 函数功能：停止 EPWM1 的工作
// 参数说明：由于其仅仅是关闭 EPWM1 的计数与转换触发所以不需要参数
//
void StopEPWM1(void)
{
    EALLOW;
    EPwm1Regs.ETSEL.bit.SOCAEN = 0;  //disable SOCA
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_FREEZE; //freeze counter
    EDIS;
}
// 下面这个函数的使用存疑，因为没有用到过
// 在之后的 DAC 控制输出时会把它用上
//void ConfigureEPWM2(Uint16 period)
//{
//    EALLOW;
//
//    EPwm2Regs.ETSEL.bit.SOCAEN    = 0;    // Disable SOC on A group
//    EPwm2Regs.ETSEL.bit.SOCASEL    = 4;   // Select SOC on up-count
//    EPwm2Regs.ETPS.bit.SOCAPRD = 1;       // Generate pulse on 1st event
//
//    // 下面这两行可以设置 epwm 的频率，但是应该注意的是
//    // 在把它运用到 adc 采样的时候，发现
//    // 随着频率增大，其实它可调节的频率很小。
//    // 其极限参数大概在 0x0010 与 0x0008 这个地方
//    // 个人猜测是因为频率太高的话，采样中有一些步骤必不可少
//    // 这些步骤最终决定了极限的采样频率
//    EPwm2Regs.CMPA.bit.CMPA = period - 1;     // Set compare A value to 8 counts
//    EPwm2Regs.TBPRD = period;             // Set period to 16 counts
//    EPwm2Regs.TBCTL.bit.CTRMODE = 3;      // freeze counter
//    EDIS;
//}
