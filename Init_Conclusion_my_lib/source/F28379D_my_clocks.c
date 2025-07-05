/*
 * F28379D_my_clocks.c
 *
 *  Created on: 2024Äê7ÔÂ18ÈÕ
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"



#include "F28379D_my_clocks.h"

void InitSystemClocks(void)
{
    InitSysCtrl();      //Enable peripheral clocks

    ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0x00;
}
