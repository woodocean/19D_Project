/*
 * BlueTooth_HC_06.c
 *
 *  Created on: 2024年7月26日
 *      Author: Lenovo
 */

// 在这个文件中将会集成化所有使用 scib 端口控制蓝牙传输的函数
// 其中将会实现的功能有连续数据传输、
// 数据接收、波形图内容传输
// 需要说明的是该库函数实现的是 HC-06 蓝牙模块与手机端 蓝牙调试器 app
// 之间的通信
// 对于蓝牙调试器这个 app 它的通信协议是一次性传输所有的参数
// 所以为了能够便于之后的调整，我将会在 H 文件中声明一个结构体来
// 实现之后的数据调整

// 可以查看该文件的最后几个函数里面定义
// 将 float int short 类型的数据转化成一个或者几个 unsigned char 类型的数据来传输

#include "F28379D_my_lib.h"

#include <BlueTooth_HC_06.h>



// 应该注意的是这个传输信息的内容大小不可以超过8个字节
// 因为我设置的字符串大小小于 8 所以如果需要传递较多的信息
// 需要更改之前设置的 BLUETOOTH_DATA 这个变量类型
void BlueTooth_send(void)
{
    scib_send(0xA5);
    scib_send_string(bluetooth_d.senddata,bluetooth_d.sendnum);
    unsigned char k = 0;
    int i;
    for(i=0;i<SENDNUM;i++)
    {
        k += bluetooth_d.senddata[i];
    }
    k = k & 0xff;
    scib_send(k);
    scib_send(0x5A);
}

void adjust_receivedata(void)
{
    int i;
    unsigned char k=0;
    for(i=0;i<RECEIVENUM;i++)
    {
        bluetooth_d.adjustdata[i]=bluetooth_d.receivedata[i+1];
        k += bluetooth_d.adjustdata[i];
    }
    if((bluetooth_d.receivedata[0]==0xA5)&&(bluetooth_d.receivedata[RECEIVENUM+2]==0xA5)&&(bluetooth_d.receivedata[RECEIVENUM+1]==k))
    {
        bluetooth_d.adjustdata[RECEIVENUM] = 'T';
    }
    else
    {
        bluetooth_d.adjustdata[RECEIVENUM] = 'F';
    }
}

//
// scibRxFifoIsr - SCIB Receive FIFO ISR
//
interrupt void scibRxFifoIsr(void)
{
    Uint16 i;
    for(i=0;i<RECEIVENUM+3;i++)
    {
        bluetooth_d.receivedata[i]=ScibRegs.SCIRXBUF.bit.SAR;  // Read data
    }

    adjust_receivedata();

    ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
    ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

    PieCtrlRegs.PIEACK.bit.ACK9 =1;       // Issue PIE ack
}



void HC_06_Init(void)
{
    ConfigureSCIB();

    int i;
    // 将传输的信息进行一个初始化
    // 将指针全部设置成一个空指针
    for(i=0;i<SENDNUM;i++)
    {
        bluetooth_d.senddata[i] = 0;
    }
    bluetooth_d.sendnum = SENDNUM;

    for(i=0;i<RECEIVENUM+1;i++)
    {
        bluetooth_d.receivedata[i] = 0;
        bluetooth_d.adjustdata[i] = 0;
    }
    bluetooth_d.receivedata[RECEIVENUM+1] = 0;
    bluetooth_d.receivedata[RECEIVENUM+2] = 0;
    bluetooth_d.receivenum = RECEIVENUM;


    // 当接受的信息字符超过或等于下面这个值的时候会触发中断
    // 出于最佳策略考虑使用相关的宏定义作为衡量基础
    ScibRegs.SCIFFRX.bit.RXFFIL = RECEIVENUM + 3;

    EALLOW;
    PieVectTable.SCIB_RX_INT = &scibRxFifoIsr;
    EDIS;
    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;   // PIE Group 9, INT3
    IER |= 0x100;                        // Enable CPU INT
}





// 将 float 值转换为 unsigned char 数组
void char_float(unsigned char *bytes, float *address)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        *(bytes + i) = *((unsigned char*) address + i);
    }
}
// 将 int 值转换成 unsigned char 数组
void char_int(unsigned char *bytes, int *address)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        *(bytes + i) = *((unsigned char*) address + i);
    }
}
// 将 short 值转换成 unsigned char 数组
void char_short(unsigned char *bytes, short *address)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        *(bytes + i) = *((unsigned char*) address + i);
    }
}
