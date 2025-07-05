/*
 * F28379D_my_sci.c
 *
 *  Created on: 2024��7��22��
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#include "F28379D_my_sci.h"

//
// ConfigureSCIB() - Configure SCIB settings
//  ���ڸú�����˵����
//  �������������Ϊ�� _LAUNCHXL_F28379D ��һ�鿪������Ƶ�
//  ���������Ӧλ�Ķ˿ڸ��ù���ѡ��
//  ���õ� SCIB ��ģʽ��
//  ����ģ����ֱ���� main �������淢�ͣ��������κ��ж�
//  ����ģ����ʹ���жϺ�����ʵ��
void ConfigureSCIB(void)
{
//  ���ڿ����� _LAUNCHXL_F28379D ����
//  ������Ķ�Ӧ�� UART �� sci ��ͨ�Ŷ˿ڽ���ֻ����ô����
//  ���е� gpio19 �Լ� gpio18 �� pin3 pin4 ���� scib �Ķ˿�
//  pin3 ----- gpio19   UART RX -> MCU
//  pin4 ----- gpio18   UART TX <- MCU
#ifdef _LAUNCHXL_F28379D
    GPIO_SetupPinMux(19, GPIO_MUX_CPU1, 2);
    GPIO_SetupPinOptions(19, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(18, GPIO_MUX_CPU1, 2);
    GPIO_SetupPinOptions(18, GPIO_OUTPUT, GPIO_ASYNC);
#endif


//  ������һ�������õ�������ʱ�ӵĵײ����
//  ����Ϊ�˱����е������޸�����ش��룬ʹ�ò����ʲ���
//  ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 0b010;

    ScibRegs.SCICCR.all = 0x0007;  // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    ScibRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    ScibRegs.SCICTL2.all = 0x0003;
    ScibRegs.SCICTL2.bit.TXINTENA = 1;
    ScibRegs.SCICTL2.bit.RXBKINTENA = 1;

//  �����ʵļ��㹫ʽ
//  BRR= (SCIHBAUD<<8) + (SCILBAUD)
//  SCI�첽������ = LSPCLK / ((BRR+1)*8)
//  BRR = LSPCLK/ (SCI�첽������*8) - 1
//  Ӧ��ע����ǣ����������Ĵ����ж��ǵͰ�λ��Ч
    ScibRegs.SCIHBAUD.bit.BAUD = 0x02;
    ScibRegs.SCILBAUD.bit.BAUD = 0x8a;

//  ������һ����Ϊ�˵�Ƭ���ڲ�����ʱʹ��
//  �������ڵ�Ƭ�Լ����Լ�ͨ�ţ��������Ӧģ���Ƿ���ڹ���
//  ScibRegs.SCICCR.bit.LOOPBKENA = 1; // Enable loop back

    ScibRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset

//  Initialize the SCI FIFO
//  ����ʹ�����ⷽʽ�ӿ���Ϣ����

//  �ر��� TX ������жϴ���
//  ScibRegs.SCIFFTX.all = 0x8000;
//  ScibRegs.SCIFFTX.bit.TXFIFORESET = 1;
    ScibRegs.SCIFFTX.all = 0xE040;

    // ʹ�� Receive FIFO interrupt
    ScibRegs.SCIFFRX.bit.RXFFIENA = 1;
    // �����ܵ���Ϣ�ַ�����������������ֵ��ʱ��ᴥ���ж�
    // ������Ѳ��Կ���ʹ�� 1 ��Ϊ��������
    ScibRegs.SCIFFRX.bit.RXFFIL = 1;

    ScibRegs.SCIFFCT.all = 0x00;
    ScibRegs.SCIFFRX.bit.RXFIFORESET = 1;

    ScibRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset
}

//
// scib_send - Transmit a character from the SCI
//  һ��ֻ�ܴ���һ���ַ�
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
//  ��ȡ��õ����ݣ����������˵ȴ�ʱ��
//  ����������ܽ��黹��ʹ���ж���ʵ�ֱȽϺ�
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
    //  ���ڿ����� _LAUNCHXL_F28379D ����
    //  ������Ķ�Ӧ�� UART �� sci ��ͨ�Ŷ˿ڽ���ֻ����ô����
    //  ���е� gpio139 �Լ� gpio56 �� pin43 pin44 ���� scic �Ķ˿�
    //  pin3 ----- gpio139   UART RX -> MCU
    //  pin4 ----- gpio56    UART TX <- MCU
    #ifdef _LAUNCHXL_F28379D
        GPIO_SetupPinMux(139, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(139, GPIO_INPUT, GPIO_PUSHPULL);
        GPIO_SetupPinMux(56, GPIO_MUX_CPU1, 6);
        GPIO_SetupPinOptions(56, GPIO_OUTPUT, GPIO_ASYNC);
    #endif


    //  ������һ�������õ�������ʱ�ӵĵײ����
    //  ����Ϊ�˱����е������޸�����ش��룬ʹ�ò����ʲ���
    //  ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 0b010;

        ScicRegs.SCICCR.all = 0x0007;  // 1 stop bit,  No loopback
                                       // No parity,8 char bits,
                                       // async mode, idle-line protocol
        ScicRegs.SCICTL1.all = 0x0003; // enable TX, RX, internal SCICLK,
                                       // Disable RX ERR, SLEEP, TXWAKE
        ScicRegs.SCICTL2.all = 0x0003;
        ScicRegs.SCICTL2.bit.TXINTENA = 1;
        ScicRegs.SCICTL2.bit.RXBKINTENA = 1;

    //  �����ʵļ��㹫ʽ
    //  BRR= (SCIHBAUD<<8) + (SCILBAUD)
    //  SCI�첽������ = LSPCLK / ((BRR+1)*8)
    //  BRR = LSPCLK/ (SCI�첽������*8) - 1
    //  Ӧ��ע����ǣ����������Ĵ����ж��ǵͰ�λ��Ч
        ScicRegs.SCIHBAUD.bit.BAUD = 0x02;
        ScicRegs.SCILBAUD.bit.BAUD = 0x8a;

    //  ������һ����Ϊ�˵�Ƭ���ڲ�����ʱʹ��
    //  �������ڵ�Ƭ�Լ����Լ�ͨ�ţ��������Ӧģ���Ƿ���ڹ���
    //  ScicRegs.SCICCR.bit.LOOPBKENA = 1; // Enable loop back

        ScicRegs.SCICTL1.all = 0x0023;     // Relinquish SCI from Reset

    //  Initialize the SCI FIFO
    //  ����ʹ�����ⷽʽ�ӿ���Ϣ����

    //  �ر��� TX ������жϴ���
    //  ScicRegs.SCIFFTX.all = 0x8000;
    //  ScicRegs.SCIFFTX.bit.TXFIFORESET = 1;
        ScicRegs.SCIFFTX.all = 0xE040;

        // ʹ�� Receive FIFO interrupt
        ScicRegs.SCIFFRX.bit.RXFFIENA = 1;
        // �����ܵ���Ϣ�ַ�����������������ֵ��ʱ��ᴥ���ж�
        // ������Ѳ��Կ���ʹ�� 1 ��Ϊ��������
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
//  ��ȡ��õ����ݣ����������˵ȴ�ʱ��
//  ����������ܽ��黹��ʹ���ж���ʵ�ֱȽϺ�
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



// Ϊ�˱���֮�������ص��޸�ʹ�ã������ṩһ��ͳһ��ʹ�ú���
// ������һ���ֽ��ᱻע�͵�����Ҫ��ʱ����ʹ��

//PieVectTable.SCIC_RX_INT = &scicRxFifoIsr;
//PieCtrlRegs.PIEIER8.bit.INTx5 = 1;   // PIE Group 8, INT5, SCIC Receive Interrupt
//
//interrupt void scicRxFifoIsr(void)
//{
//    // ��ʹ������жϺ�����ȡ���ݵ���Ϣʱ
//    // ������Ҫ���������ʵ��׼ȷ��ȡ
//    // ���Ը���ͨ��֮�����Ϣ��ȷ��
//    // ����˵�������� 0xff 0xff 0xff
//    // �ڽ��յ�����źź��ֹͣͨ�ŵȴ�
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
