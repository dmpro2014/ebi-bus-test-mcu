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
#include <math.h>

uint16_t color = 0x0000;

typedef struct point {
	int x;
	int y;
} point;

int sgn(int a) {
	return a >= 0 ? 1 : -1;
}

uint16_t *BANK0_BASE_ADDR = 0x80000000;
uint16_t *framebuf_addr = 0x80000000;

void plot_pixel(int x, int y, uint16_t color) {
	if (y >= 128 || x >= 128) return;
	if (y < 0 || x < 0) return;
	*(framebuf_addr + 128 * y + x) = color;
}

/**************************************************************************
 *  line_fast                                                             *
 *    draws a line using Bresenham's line-drawing algorithm, which uses   *
 *    no multiplication or division.                                      *
 **************************************************************************/

void line_fast(int x1, int y1, int x2, int y2)
{
  int i,dx,dy,sdx,sdy,dxabs,dyabs,x,y,px,py;

  dx=x2-x1;      /* the horizontal distance of the line */
  dy=y2-y1;      /* the vertical distance of the line */
  dxabs=abs(dx);
  dyabs=abs(dy);
  sdx=sgn(dx);
  sdy=sgn(dy);
  x=dyabs>>1;
  y=dxabs>>1;
  px=x1;
  py=y1;

  if (dxabs>=dyabs) /* the line is more horizontal than vertical */
  {
    for(i=0;i<dxabs;i++)
    {
      y+=dyabs;
      if (y>=dxabs)
      {
        y-=dxabs;
        py+=sdy;
      }
      px+=sdx;
      plot_pixel(px,py,color);
    }
  }
  else /* the line is more vertical than horizontal */
  {
    for(i=0;i<dyabs;i++)
    {
      x+=dxabs;
      if (x>=dyabs)
      {
        x-=dyabs;
        px+=sdx;
      }
      py+=sdy;
      plot_pixel(px,py,color);
    }
  }
}

void screen_clear() {
	for(int i = 0; i < 128*128; i++) {
		*(framebuf_addr + i) = 0b1111111111100000;
	}
}

void demo_cube(void) {


        // Source X, Y and Z of each point of the cube.
        int x, y, z;

        // Rotation in X and Y.
        float rx = 0, ry = 0;

        // Computed sin/cos of the rotated X and Y.
        float sin_rx, cos_rx, sin_ry, cos_ry;

        // Transformed X, Y and Z.
        float tx, ty, tz;

        // Stores the eight projected vertices.
        point vertices[8];

        // There's always a need for one of these.
        unsigned int i;

        // Size of the cube.
        float rs = 0;
        float s;

        unsigned int demo_timer = 315;

        int buffer = 0;

        while (demo_timer--) {

                // Calculate the sin/cos of the rotated X and Y.
                sin_rx = sin(rx);
                cos_rx = cos(rx);
                sin_ry = sin(ry);
                cos_ry = cos(ry);

                // Calculate the size of the cube.
                s = 40.0f * (1.0f - cos(rs));

                // Calculate each vertex in turn.
                i = 0;
                for (x = -1; x <= +1; x += 2) {
                        for (y = -1; y <= +1; y += 2) {
                                for (z = -1; z <= +1; z+= 2) {

                                        // Calculate the transformed vertex.
                                        tx = y * cos_rx - x * sin_rx;
                                        ty = -x * cos_rx * sin_ry - y * sin_rx * sin_ry - z * cos_ry;
                                        tz = 3 - x * cos_rx * cos_ry - y * sin_rx * cos_ry + z * sin_ry;

                                        // Project and store.
                                        vertices[i].x = 64 + (int)(tx * s / tz);
                                        vertices[i].y = 64 + (int)(ty * s / tz);

                                        // Advance to the next vertex.
                                        ++i;
                                }
                        }
                }

                // Wait to return back to first scanline.
                // while (lcd_scan_row);

                // Clear the LCD.
                screen_clear();

                // One face.
                line_fast(vertices[0].x, vertices[0].y, vertices[1].x, vertices[1].y);
                line_fast(vertices[1].x, vertices[1].y, vertices[3].x, vertices[3].y);
                line_fast(vertices[3].x, vertices[3].y, vertices[2].x, vertices[2].y);
                line_fast(vertices[2].x, vertices[2].y, vertices[0].x, vertices[0].y);

                // Opposite face.
                line_fast(vertices[4].x, vertices[4].y, vertices[5].x, vertices[5].y);
                line_fast(vertices[5].x, vertices[5].y, vertices[7].x, vertices[7].y);
                line_fast(vertices[7].x, vertices[7].y, vertices[6].x, vertices[6].y);
                line_fast(vertices[6].x, vertices[6].y, vertices[4].x, vertices[4].y);

                // Connecting the two faces.
                for (i = 0; i < 4; ++i) {
                        line_fast(vertices[i].x, vertices[i].y, vertices[i + 4].x, vertices[i + 4].y);
                }
                rs += 0.02f;
                ry += 0.03f;
                rx += 0.05f;
                //delay_frames(3);

                *(framebuf_addr + 0xffff) = buffer;
                buffer = !buffer;
        }

        screen_clear();
}

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

    CMU_HFRCOBandSet(cmuHFRCOBand_28MHz);

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

    /* EBI A07-A14 */
    GPIO_PinModeSet( gpioPortE,  0, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  1, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  9, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortC,  10, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  4, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  5, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  6, gpioModePushPull, 0 );
    GPIO_PinModeSet( gpioPortE,  7, gpioModePushPull, 0 );

    /* EBI A15-A18 */
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
    ebiConfig.addrHoldCycles  = 0;
    ebiConfig.addrSetupCycles = 0;


    /* Read cycle times */
    ebiConfig.readStrobeCycles = 7;
    ebiConfig.readHoldCycles   = 3;
    ebiConfig.readSetupCycles  = 3;

    /* Write cycle times */
    ebiConfig.writeStrobeCycles = 0;
    ebiConfig.writeHoldCycles   = 0;
    ebiConfig.writeSetupCycles  = 1;

    /* Configure EBI bank 0 */
    EBI_Init(&ebiConfig);



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
    ebiConfig.addrHoldCycles  = 0;
    ebiConfig.addrSetupCycles = 0;

    /* Read cycle times */
    ebiConfig.readStrobeCycles = 0;
    ebiConfig.readHoldCycles   = 0;
    ebiConfig.readSetupCycles  = 0;

    /* Write cycle times */
    ebiConfig.writeStrobeCycles = 0;
    ebiConfig.writeHoldCycles   = 0;
    ebiConfig.writeSetupCycles  = 0;

    /* Configure EBI bank 1 */
    EBI_Init(&ebiConfig);

    uint16_t *BANK1_BASE_ADDR = 0x84000000;

/* --------------------------------------------------------- */

  /* Infinite loop */
    int FRAME_WIDTH = 128;
    int FRAME_SIZE = FRAME_WIDTH * FRAME_WIDTH;


    uint16_t colorRed, colorGreen, colorBlue, colorWhite; // 16-bit pixel values
    colorGreen = 	0b1111100000000000; // Green=max, Red=0, Blue=0
    colorRed = 		0b0101111111100011; // Green=0, Red=max, Blue=0
    colorBlue = 	0b0001100001111111; // Green=0, Red=0, Blue=max
    colorWhite =    0b1111111111111111;

    while(1) {
    	demo_cube();
    }
}
