/***************************************************************
main.c

Democode voor vga_api library.

(c) Jos, Tijmen, Niels 05/2017
***************************************************************/

#include "main.h"
#include "stm32_ub_vga_screen.h"
#include "vga_api.h"
#include <math.h>
#include <stdbool.h>


int main(void)
{
	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen
	UB_VGA_FillScreen(VGA_COL_BLACK);
  //UB_VGA_SetPixel(10,10,10);

	  uint16_t x_lo = 100;
	  uint16_t y_lo = 200;
	  uint16_t x_rb = 200;
	  uint16_t y_rb = 100;
	  uint8_t rechthoek_kleur = 31;

	  //Teken rechthoek
	  rechthoek(x_lo, y_lo, x_rb, y_rb, 1, rechthoek_kleur, 0);


	  uint16_t x_l = 50;
	  uint16_t y_l = 50;
	  uint16_t x_r = 100;
	  uint16_t y_r = 100;
	  uint8_t lijn_kleur = 70;
	  uint8_t dikte = 1;

	  //Teken lijn
	  //lijn(x_l, y_l, x_r, y_r, dikte, lijn_kleur);

  while(1)
  {
	  // put the code here
  }
}

