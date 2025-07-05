/*
 * F28379D_my_sci.c
 *
 *  Created on: 2024年7月22日
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#include "F28379D_my_sci.h"

//
// ConfigureSCIB() - Configure SCIB settings
//  对于该函数的说明：
//  这个函数主打是为了 _LAUNCHXL_F28379D 这一块开发板设计的
//  设置了其对应位的端口复用功能选择
//  设置的 SCIB 的模式是
//  发送模块是直接在 main 函数里面发送，不启用任何中断
//  接收模块是使用中断函数来实现
void ConfigureSCIB(void)
{
//  对于开发板 _LAUNCHXL_F28379D 而言
//  它上面的对应于 UART 即 sci 的通信端口仅仅只有那么几个
//  其中的 gpio19 以及 gpio18 即 pin3 pin4 就是 scib 的端口
//  pin3 ----- gpio19   UART RX -> MCU
//  pin4 ----- gpio18   UART TX <- MCU
#ifdef _LAUNCHXL_F28379D
    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2);
    GPIO_SetupPinOptions(19, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2);
    GPIO_SetupPinOptions(18, GPIO_OUTPUT, GPIO_ASYNC);
#endif


//  下面这一行是设置低速外设时钟的底层代码
//  这是为了避免有的外设修改了相关代码，使得波特率不对
//  ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 0b010;

    ScibRegs.SCICCR.all = 0x0007;  // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    ScibRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    ScibRegs.SCICTL2.all = 0x0003;
    ScibRegs.SCICTL2.bit.TXINTENA = 1;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;

//  波特率的计算公式
//  BRR= (SCIHBAUD<<8) + (SCILBAUD)
//  SCI异步波特率 = LSPCLK / ((BRR+1)*8)
//  BRR = LSPCLK/ (SCI异步波特率*8) - 1
//  应当注意的是，下面两个寄存器中都是低八位有效
    ScibRegs.SCIHBAUD.bit.BAUD = 0x02;
    ScibRegs.SCILBAUD.bit.BAUD = 0x8a;

//  下面这一行是为了单片机内部测试时使用
//  它是用于单片自己与自己通信，来检测相应模块是否存在故障
//  ScibRegs.SCICCR.bit.LOOPBKENA = 1; // Enable loop back

    ScibRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset

//  Initialize the SCI FIFO
//  这是使用特殊方式加快信息传输

//  关闭了 TX 的完成中断触发
//  ScibRegs.SCIFFTX.all = 0x8000;
//  ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;
    ScibRegs.SCIFFTX.all = 0xE040;

    // 使能 Receive FIFO interrupt
    ScibRegs.SCIFFRX.bit.RXFFIENA = 1;
    // 当接受的信息字符超过或等于下面这个值的时候会触发中断
    // 出于最佳策略考虑使用 1 作为衡量基础
    ScibRegs.SCIFFRX.bit.RXFFIL = 1;

    ScibRegs.SCIFFCT.all = 0x00;
    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;

    ScibRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
}

//
// scib_send - Transmit a character from the SCI
//  一次只能传递一个字符
void scib_send(unsigned char a)
{
    ScibRegs.SCITXBUF.bit.TXDT=a;
}

void scib_send_string(unsigned char *a,unsigned int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        scib_send(a[i]&0x00FF);
    }
}

//
//  scib_read()
//  读取获得的数据，并且设置了等待时间
//  对于这个功能建议还是使用中断来实现比较好
unsigned char scib_read(void)
{
    //
    // wait for RRDY/RXFFST =1 for 1 data available in FIFO
    //
    while(ScibRegs.SCIFFRX.bit.RXFFST == 0);


    return ScibRegs.SCIRXBUF.bit.SAR;
}





void ConfigureSCIC(void)
{
    {
    //  对于开发板 _LAUNCHXL_F28379D 而言
    //  它上面的对应于 UART 即 sci 的通信端口仅仅只有那么几个
    //  其中的 gpio139 以及 gpio56 即 pin43 pin44 就是 scic 的端口
    //  pin3 ----- gpio139   UART RX -> MCU
    //  pin4 ----- gpio56    UART TX <- MCU
    #ifdef _LAUNCHXL_F28379D
        GPIO_SetupPinMux(139, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(139, GPIO_INPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(56, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(56, GPIO_OUTPUT, GPIO_ASYNC);
    #endif


    //  下面这一行是设置低速外设时钟的底层代码
    //  这是为了避免有的外设修改了相关代码，使得波特率不对
    //  ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 0b010;

        ScicRegs.SCICCR.all = 0x0007;  // 1 stop bit,  No loopback
                                       // No parity,8 char bits,
                                       // async mode, idle-line protocol
        ScicRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
                                       // Disable RX ERR, SLEEP, TXWAKE
        ScicRegs.SCICTL2.all = 0x0003;
        ScicRegs.SCICTL2.bit.TXINTENA = 1;
        ScicRegs.SCICTL2.bit.RXBKINTENA = 1;

    //  波特率的计算公式
    //  BRR= (SCIHBAUD<<8) + (SCILBAUD)
    //  SCI异步波特率 = LSPCLK / ((BRR+1)*8)
    //  BRR = LSPCLK/ (SCI异步波特率*8) - 1
    //  应当注意的是，下面两个寄存器中都是低八位有效
        ScicRegs.SCIHBAUD.bit.BAUD = 0x02;
        ScicRegs.SCILBAUD.bit.BAUD = 0x8a;

    //  下面这一行是为了单片机内部测试时使用
    //  它是用于单片自己与自己通信，来检测相应模块是否存在故障
    //  ScicRegs.SCICCR.bit.LOOPBKENA = 1; // Enable loop back

        ScicRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset

    //  Initialize the SCI FIFO
    //  这是使用特殊方式加快信息传输

    //  关闭了 TX 的完成中断触发
    //  ScicRegs.SCIFFTX.all = 0x8000;
    //  ScicRegs.SCIFFTX.bit.TXFIFORESET = 1;
        ScicRegs.SCIFFTX.all = 0xE040;

        // 使能 Receive FIFO interrupt
        ScicRegs.SCIFFRX.bit.RXFFIENA = 1;
        // 当接受的信息字符超过或等于下面这个值的时候会触发中断
        // 出于最佳策略考虑使用 1 作为衡量基础
        ScicRegs.SCIFFRX.bit.RXFFIL = 1;

        ScicRegs.SCIFFCT.all = 0x00;
        ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;

        ScicRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
    }
}
void scic_send(unsigned char a)
{
    ScicRegs.SCITXBUF.bit.TXDT=a;
}

//
//  scic_read()
//  读取获得的数据，并且设置了等待时间
//  对于这个功能建议还是使用中断来实现比较好
unsigned char scic_read(void)
{
    //
    // wait for RRDY/RXFFST =1 for 1 data available in FIFO
    //
    while(ScicRegs.SCIFFRX.bit.RXFFST == 0);


    return ScicRegs.SCIRXBUF.bit.SAR;
}
void scic_send_string(unsigned char *a, unsigned int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        scic_send(a[i]&0x00FF);
    }
}



// 为了便于之后进行相关的修改使用，这里提供一份统一的使用函数
// 并且这一部分将会被注释掉，需要的时侯再使用

//PieVectTable.SCIC_RX_INT = &scicRxFifoIsr;
//PieCtrlRegs.PIEIER8.bit.INTx5 = 1;   // PIE Group 8, INT5, SCIC Receive Interrupt
//
//interrupt void scicRxFifoIsr(void)
//{
//    // 在使用这个中断函数读取传递的信息时
//    // 可能需要重新设计来实现准确读取
//    // 可以根据通信之间的信息来确定
//    // 比如说连续三个 0xff 0xff 0xff
//    // 在接收到这个信号后就停止通信等待
//    static Uint16 i;
//    if(i<11)
//    {
//        ReceivedChar[i]=ScicRegs.SCIRXBUF.bit.SAR;  // Read data
//        i++;
//    }
//    else
//    {
//        ReceivedChar[0]=ScicRegs.SCIRXBUF.bit.SAR;  // Read data
//        i=0;
//    }
//
//    ScicRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
//    ScicRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag
//
//    PieCtrlRegs.PIEACK.bit.ACK8 =1;       // Issue PIE ack
//}
