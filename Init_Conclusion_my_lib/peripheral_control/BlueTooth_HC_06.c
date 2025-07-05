/*
 * BlueTooth_HC_06.c
 *
 *  Created on: 2024��7��26��
 *      Author: Lenovo
 */

// ������ļ��н��Ἧ�ɻ�����ʹ�� scib �˿ڿ�����������ĺ���
// ���н���ʵ�ֵĹ������������ݴ��䡢
// ���ݽ��ա�����ͼ���ݴ���
// ��Ҫ˵�����Ǹÿ⺯��ʵ�ֵ��� HC-06 ����ģ�����ֻ��� ���������� app
// ֮���ͨ��
// ����������������� app ����ͨ��Э����һ���Դ������еĲ���
// ����Ϊ���ܹ�����֮��ĵ������ҽ����� H �ļ�������һ���ṹ����
// ʵ��֮������ݵ���

// ���Բ鿴���ļ�����󼸸��������涨��
// �� float int short ���͵�����ת����һ�����߼��� unsigned char ���͵�����������

#include "F28379D_my_lib.h"

#include <BlueTooth_HC_06.h>



// Ӧ��ע��������������Ϣ�����ݴ�С�����Գ���8���ֽ�
// ��Ϊ�����õ��ַ�����СС�� 8 ���������Ҫ���ݽ϶����Ϣ
// ��Ҫ����֮ǰ���õ� BLUETOOTH_DATA �����������
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
    // ���������Ϣ����һ����ʼ��
    // ��ָ��ȫ�����ó�һ����ָ��
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


    // �����ܵ���Ϣ�ַ�����������������ֵ��ʱ��ᴥ���ж�
    // ������Ѳ��Կ���ʹ����صĺ궨����Ϊ��������
    ScibRegs.SCIFFRX.bit.RXFFIL = RECEIVENUM + 3;

    EALLOW;
    PieVectTable.SCIB_RX_INT = &scibRxFifoIsr;
    EDIS;
    PieCtrlRegs.PIEIER9.bit.INTx3 = 1;   // PIE Group 9, INT3
    IER |= 0x100;                        // Enable CPU INT
}





// �� float ֵת��Ϊ unsigned char ����
void char_float(unsigned char *bytes, float *address)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        *(bytes + i) = *((unsigned char*) address + i);
    }
}
// �� int ֵת���� unsigned char ����
void char_int(unsigned char *bytes, int *address)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        *(bytes + i) = *((unsigned char*) address + i);
    }
}
// �� short ֵת���� unsigned char ����
void char_short(unsigned char *bytes, short *address)
{
    int i;
    for (i = 0; i < 2; i++)
    {
        *(bytes + i) = *((unsigned char*) address + i);
    }
}
