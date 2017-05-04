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

	  uint16_t x_lo = 100;
	  uint16_t y_lo = 200;
	  uint16_t x_rb = 200;
	  uint16_t y_rb = 100;
	  uint8_t rechthoek_dikte = 5;
	  uint8_t rechthoek_kleur = VGA_COL_BLUE;
	  bool gevuld = 0;

	  //Teken rechthoek
	  //rechthoek(x_lo, y_lo, x_rb, y_rb, rechthoek_dikte, rechthoek_kleur, gevuld);



	  uint16_t x_l = 50;
	  uint16_t y_l = 50;
	  uint16_t x_r = 100;
	  uint16_t y_r = 100;
	  uint8_t lijn_kleur = 70;
	  uint8_t lijn_dikte = 1;

	  //Teken lijn
	  //lijn(x_l, y_l, x_r, y_r, lijn_dikte, lijn_kleur);

  while(1)
  {
	  //Rechthoek demo
	  for(int i = 0; i <240; i++)
	  {
		  UB_VGA_FillScreen(VGA_COL_BLACK);
		  rechthoek(0, 239, i, (239-i), 1, VGA_COL_BLUE, 0);
		  for(int j = 0; j <100000; j++);
	  }
	  for (int k = 0; k <120; k++)
	  {
		  rechthoek(0, 239, 239, 0, k, VGA_COL_BLUE, 0);
		  for(int j = 0; j <(100000/2); j++);
	  }

  }
}

