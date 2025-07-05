/*
 * F28379D_my_flash.c
 *
 *  Created on: 2024年7月18日
 *      Author: Lenovo
 */

#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#include "F28379D_my_flash.h"

#ifdef FLASH
void Init_Flash(void)
{
    EALLOW;

    // 这一段在原本是单独被放在主程序中的。
    // 但是经过我个人的思考认定它放到这个函数里面并不会有什么影响
    // 为了简洁考虑，我把它放到这里面来了
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
    memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
            (uint32_t)&RamfuncsLoadSize );
    //


    //At reset bank and pump are in sleep
    //A Flash access will power up the bank and pump automatically
    //After a Flash access, bank and pump go to low power mode (configurable in
    //FBFALLBACK/FPAC1 registers)-
    //if there is no further access to flash
    //Power up Flash bank and pump and this also sets the fall back mode of
    //flash and pump as active
    Flash0CtrlRegs.FPAC1.bit.PMPPWR = 0x1;
    Flash0CtrlRegs.FBFALLBACK.bit.BNKPWR0 = 0x3;

    //Disable Cache and prefetch mechanism before changing wait states
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 0;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 0;

    //Set waitstates according to frequency
    //CAUTION
    //Minimum waitstates required for the flash operating
    //at a given CPU rate must be characterized by TI.
    //Refer to the datasheet for the latest information.
#if CPU_FRQ_200MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x3;
#endif

#if CPU_FRQ_150MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
#endif

#if CPU_FRQ_120MHZ
    Flash0CtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
#endif

    //Enable Cache and prefetch mechanism to improve performance
    //of code executed from Flash.
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.DATA_CACHE_EN = 1;
    Flash0CtrlRegs.FRD_INTF_CTRL.bit.PREFETCH_EN = 1;

    //At reset, ECC is enabled
    //If it is disabled by application software and if application again wants
    //to enable ECC
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0xA;

    EDIS;

    //Force a pipeline flush to ensure that the write to
    //the last register configured occurs before returning.

    __asm(" RPT #7 || NOP");
}
#endif

// End of file
