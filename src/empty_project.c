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

/* --- Configure GPIO pins as push pull -------------------- */

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
/* First bank needs a name, Bank 0, Base Address 0x80000000  */
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

    uint16_t *BANK0_BASE_ADDR = 0x80000000;

/* --------------------------------------------------------- */
/* Second bank needs a name, Bank 1, Base Address 0x84000000 */
/* --------------------------------------------------------- */
    ebiConfig.banks       = EBI_BANK1;
    ebiConfig.csLines     = EBI_CS1;
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

    /* Configure EBI bank 1 */
    EBI_Init(&ebiConfig);

    uint16_t *BANK1_BASE_ADDR = 0x84000000;

/* --------------------------------------------------------- */

  /* Infinite loop */
    int FRAME_SIZE = 128*128;
    uint16_t *framebuf_addr = BANK0_BASE_ADDR;

    uint16_t colorRed, colorGreen, colorBlue; // 16-bit pixel values
    colorGreen = 	0b 11111 000000 00000; // Green=max, Red=0, Blue=0
    colorRed = 		0b0000011111100000; // Green=0, Red=max, Blue=0
    colorBlue = 	0b0000000000011111; // Green=0, Red=0, Blue=max


    for(int offset = 0; offset < FRAME_SIZE; offset++) {
    	*(framebuf_addr + offset) = ~colorRed;
    }

    for(int offset = 0; offset < FRAME_SIZE; offset++) {
    	*(framebuf_addr + offset) = ~colorGreen;
    }

    for(int offset = 0; offset < FRAME_SIZE; offset++) {
    	*(framebuf_addr + offset) = ~colorBlue;
    }

}
