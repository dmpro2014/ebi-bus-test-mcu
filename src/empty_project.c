/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_ebi.h"
#include "em_gpio.h"
#include "em_cmu.h"

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  /* Chip errata */
  CHIP_Init();

  EBI_Init_TypeDef ebiConfig = EBI_INIT_DEFAULT;

    /* Enable clocks */
    CMU_ClockEnable(cmuClock_EBI, true);
    CMU_ClockEnable(cmuClock_GPIO, true);

    /* Giant or Leopard family. */

    /* Configure GPIO pins as push pull */
    /* EBI AD9..15 */
    GPIO_PinModeSet( gpioPortA,  0, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  1, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  2, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  3, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  4, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  5, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA,  6, gpioModePushPull, 0 );

    /* EBI AD8 */
    GPIO_PinModeSet( gpioPortA, 15, gpioModePushPull, 0 );

    /* EBI A00-A06 */
    GPIO_PinModeSet( gpioPortA, 12, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA, 13, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA, 14, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB, 10, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  6, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  7, gpioModePushPull, 0 );

    /* EBI A07-A */
    GPIO_PinModeSet( gpioPortE,  0, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  1, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  2, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  3, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  4, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  5, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  6, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  7, gpioModePushPull, 0 );

    /* EBI A00-A18 */
    GPIO_PinModeSet( gpioPortA, 12, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA, 13, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortA, 14, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB, 10, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  6, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  7, gpioModePushPull, 0 );


    GPIO_PinModeSet( gpioPortC,  8, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  0, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  1, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortB,  2, gpioModePushPull, 0 );

    /* EBI CS0-CS3 */
    GPIO_PinModeSet( gpioPortD,  9, gpioModePushPull, 1 );
    GPIO_PinModeSet( gpioPortD, 10, gpioModePushPull, 1 );
    GPIO_PinModeSet( gpioPortD, 11, gpioModePushPull, 1 );
    GPIO_PinModeSet( gpioPortD, 12, gpioModePushPull, 1 );

    /* EBI AD0..7 */
    GPIO_PinModeSet( gpioPortE,  8, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 10, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 11, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 12, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 13, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 14, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE, 15, gpioModePushPull, 0 );

    /* EBI ARDY/WEN/REN/ALE */
    GPIO_PinModeSet( gpioPortF,  2, gpioModeInput,    0 );
    GPIO_PinModeSet( gpioPortF,  8, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortF,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC, 11, gpioModePushPull, 0 );

    /* EBI Byte Lane 0 support BL0/BL1 */
    GPIO_PinModeSet( gpioPortF, 6, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortF, 7, gpioModePushPull, 0 );

    /* --------------------------------------------------------- */
    /* Board Control Registers, Bank 0, Base Address 0x80000000  */
    /* FPGA Xilinx Spartan XC6SLX9 CSG324                        */
    /* --------------------------------------------------------- */
    ebiConfig.banks       = EBI_BANK0;
    ebiConfig.csLines     = EBI_CS0;
    ebiConfig.mode        = ebiModeD16;
    ebiConfig.alePolarity = ebiActiveHigh;
    ebiConfig.location    = ebiLocation1;
    /* keep blEnable */
    ebiConfig.blEnable     = false;
    ebiConfig.addrHalfALE  = false;
    ebiConfig.readPrefetch = false;
    ebiConfig.noIdle       = true;

    /* keep alow/ahigh configuration */
    ebiConfig.aLow = ebiALowA0;
    ebiConfig.aHigh = ebiAHighA19;

    /* Address Setup and hold time */
    ebiConfig.addrHoldCycles  = 3;
    ebiConfig.addrSetupCycles = 3;

    /* Read cycle times */
    ebiConfig.readStrobeCycles = 7;
    ebiConfig.readHoldCycles   = 3;
    ebiConfig.readSetupCycles  = 3;

    /* Write cycle times */
    ebiConfig.writeStrobeCycles = 7;
    ebiConfig.writeHoldCycles   = 3;
    ebiConfig.writeSetupCycles  = 3;

    /* Configure EBI bank 0 */
    EBI_Init(&ebiConfig);

  /* Infinite loop */
    uint16_t *address;
    address = 0x80000000;
  while (1) {
	  *address = 0xffff;
	  *(address+1) = 0xaaaa;
	  *(address+2) = 0x8888;
	  *(address+10) = 0x0001;
  }
}