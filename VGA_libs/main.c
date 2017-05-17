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
#include "bitmaps.h"

int main(void)
{
	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen
	clearscherm(VGA_COL_BLACK);

/*
	  uint16_t x_lo = 100;
	  uint16_t y_lo = 200;
	  uint16_t x_rb = 200;
	  uint16_t y_rb = 100;
	  uint8_t rechthoek_dikte = 5;
	  uint8_t rechthoek_kleur = VGA_COL_BLUE;
	  bool gevuld = 0;

	  // Teken rechthoek
	  rechthoek(x_lo, y_lo, x_rb, y_rb, rechthoek_dikte, rechthoek_kleur, gevuld);

	  uint16_t x_l = 50;
	  uint16_t y_l = 50;
	  uint16_t x_r = 100;
	  uint16_t y_r = 100;
	  uint8_t lijn_kleur = 70;
	  uint8_t lijn_dikte = 1;

	  // Teken lijn
	  lijn(x_l, y_l, x_r, y_r, lijn_dikte, lijn_kleur);
*/

	  // Bitmap demo
	  bitmap(25, 100, &emoji_blij_64);
	  bitmap(100, 100, &emoji_boos_64);
	  bitmap(175, 100, &HU_logo_50);
	  bitmap(25, 200, &pijl_omhoog_60);
	  bitmap(100, 200, &pijl_omlaag_60);
	  bitmap(175, 200, &pijl_links_60);
	  bitmap(250, 200, &pijl_rechts_60);

  while(1)
  {
	  	  /*
	  	  // Rechthoek coördinaten demo
	  	  for(int i = 0; i <240; i++)
	  	  {
	  		  clearscherm(VGA_COL_BLACK);
	  		  rechthoek(0, 239, i, (239-i), 5, VGA_COL_BLUE, 0);
	  		  for(int j = 0; j <100000; j++);
	  	  }

	  	  // Rechthoek dikte demo
	  	  for (int k = 0; k <76; k++)
	  	  {
	  		  rechthoek(50, 200, 200, 50, k, VGA_COL_CYAN, 0);
	  		  for(int j = 0; j <(100000); j++);
	  	  }

	  	  // Beeld vasthouden
	  	  for(int j = 0; j <(100000000); j++);
	  	  */
  }
}

