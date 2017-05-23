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
	// Start clocks
	SystemInit();

	// Start VGA
	UB_VGA_Screen_Init();

	// Zet scherm op zwart
	clearscherm(ZWART);

/*
	// Rechthoek demo
	rechthoek(0, 239, 319, 0, 10, VGA_COL_WHITE, 0);
	rechthoek(20, 225, 300, 20, 3, VGA_COL_RED, 0);
	rechthoek(25, 220, 100, 25, 1, VGA_COL_BLUE, 1);
	rechthoek(150, 130, 250, 30, 1, VGA_COL_GREEN, 1);
	rechthoek(175, 200, 200, 175, 2, VGA_COL_MAGENTA, 0);
*/

/*
	  // Lijn demo
	  lijn(0, 10, 200, 10, 10, VGA_COL_BLUE);
	  lijn(0, 30, 100, 50, 5, VGA_COL_RED);
	  lijn(0, 100, 200, 50, 1, VGA_COL_GREEN);
	  lijn(50, 200, 100, 100, 20, VGA_COL_YELLOW);
	  lijn(220, 10, 220, 220, 1, VGA_COL_WHITE);
*/


/*
	  // Bitmap demo
	  bitmap(25, 100, &emoji_blij_64);
	  bitmap(100, 100, &emoji_boos_64);
	  bitmap(175, 100, &HU_logo_50);
	  bitmap(25, 200, &pijl_omhoog_60);
	  bitmap(100, 200, &pijl_omlaag_60);
	  bitmap(175, 200, &pijl_links_60);
	  bitmap(250, 200, &pijl_rechts_60);
*/

	/*
	// Kleuren demo
	lijn(0,10,239,10, 5, BLAUW);
	lijn(0,20,239,20, 5, LICHTBLAUW);
	lijn(0,30,239,30, 5, GROEN);
	lijn(0,40,239,40, 5, LICHTGROEN);
	lijn(0,50,239,50, 5, ROOD);
	lijn(0,60,239,60, 5, LICHTROOD);
	lijn(0,70,239,70, 5, CYAAN);
	lijn(0,80,239,80, 5, LICHTCYAAN);
	lijn(0,90,239,90, 5, MAGENTA);
	lijn(0,100,239,100, 5, LICHTMAGENTA);
	lijn(0,110,239,110, 5, BRUIN);
	lijn(0,120,239,120, 5, GEEL);
	lijn(0,130,239,130, 5, GRIJS);
	lijn(0,140,239,140, 5, WIT);
*/

  while(1)
  {
	  	  /*
	  	  // Rechthoek formaat demo
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

