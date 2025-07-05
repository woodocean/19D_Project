/*
 * BlueTooth_HC_06.h
 *
 *  Created on: 2024年7月26日
 *      Author: Lenovo
 */

#include "F28x_Project.h"

#ifndef INIT_CONCLUSION_MY_LIB_PERIPHERAL_CONTROL_BLUETOOTH_HC_06_H_
#define INIT_CONCLUSION_MY_LIB_PERIPHERAL_CONTROL_BLUETOOTH_HC_06_H_


// 在确定好之后的蓝牙与手机之间传输的
// 数据格式后应该这两个值是确定的
// 所以完全可以先确定下来
// 这个传输的变量类型其实还是并不完全确定的
// 需要根据具体的要求来进行修改
// 现在仅仅只是做一个示例
// 甚至完全有可能在之后的时候需要强转一个
// float 类型的数据为四个 unsigned char 类型的数据
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
