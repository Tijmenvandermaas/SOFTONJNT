/***************************************************************
vga_api.h


HU Software Ontwikkeling.
(c) Jos, Tijmen, Niels 05/2017
***************************************************************/

/***************************
Includes
***************************/
#include "vga_api.h"


/***************************

***************************/
void tekst(uint16_t x, uint16_t y, uint8_t tekst[100], uint8_t font,  uint8_t grootte,  uint8_t kleur,  uint8_t stijl)
{

}

/***************************

***************************/
void lijn(uint16_t x_l, uint16_t y_l, uint16_t x_r, uint16_t y_r, uint8_t dikte, uint8_t kleur)
{

}

/***************************

***************************/
void ellips(uint16_t x_mp, uint16_t y_mp, uint16_t radius_x, uint16_t radius_y, uint8_t dikte, uint8_t kleur, bool gevuld)
{

}

/***************************
Rechthoek: teken een rechthoek.
(x_lo, y_lo, x_rb, y_rb, dikte, kleur, gevuld)
(c) Jos van Mourik
***************************/
void rechthoek(uint16_t x_lo, uint16_t y_lo, uint16_t x_rb, uint16_t y_rb, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	// Tekenen buiten scherm voorkomen
	if(x_rb>=VGA_DISPLAY_X) x_rb = VGA_DISPLAY_X-1;
	if(y_lo>=VGA_DISPLAY_Y) y_lo = VGA_DISPLAY_Y-1;

	// Gevulde rechthoek of overflow lijndikte
	if(gevuld || dikte >= ((x_rb-x_lo)/2) || dikte >= ((y_lo-y_rb)/2))
	{
		// Verticale coördinaten
		for (uint16_t y = y_rb; y < (y_lo+1); y++)
		{
			// Horizontale coördinaten
			for(uint16_t x = x_lo; x < (x_rb+1); x++)
			{
				setpixel(x, y, kleur);
			}
		}
	}

	else
	{
		// Teken lijndikte
		for(uint8_t d = 0; d < dikte; d++)
		{
			// Teken horizontale lijnen van rechthoek
			for(uint16_t x = x_lo; x < (x_rb+1); x++)
			{
				setpixel(x, (y_rb+d), kleur);
				setpixel(x, (y_lo-d), kleur);
			}

			// Teken verticale lijnen van rechthoek
			for(uint16_t y = (y_rb+dikte); y < (y_lo+1-dikte); y++)
			{
				setpixel((x_lo+d), y, kleur);
				setpixel((x_rb-d), y, kleur);
			}
		}
	}
}

/***************************

***************************/
void driehoek(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint16_t x_3, uint16_t y_3, uint8_t dikte, uint8_t kleur, bool gevuld)
{

}

/***************************
Setpixel: verandert één pixel van kleur.
(x, y, kleur)
(c) Franc van der Bent, aangepast door Jos van Mourik
***************************/
void setpixel(uint16_t x, uint16_t y, uint8_t kleur)
{
	if((x<VGA_DISPLAY_X) && (y<VGA_DISPLAY_Y)) VGA_RAM1[(y*(VGA_DISPLAY_X+1))+x] = kleur;
}

/***************************
Readpixel: geef de waarde van één pixel terug.
(x, y)
(c) Jos van Mourik
***************************/
uint8_t readpixel(uint16_t x, uint16_t y)
{
	if((x<VGA_DISPLAY_X) && (y<VGA_DISPLAY_Y)) return VGA_RAM1[(y*(VGA_DISPLAY_X+1))+x];
	else return 0;
}

/***************************
bitmap:
(x_lo, y_lo, map)
(c) Jos van Mourik

To do: support voor bitmaps die niet een factor 8 formaat hebben
***************************/
void bitmap(uint16_t x_lo, uint16_t y_lo, char map[])
{
	// Start bitmap data in array
	uint16_t cursor = 4;

	// Bereken startpunt ten opzichte van linksonder
	for(uint16_t y = (y_lo-map[2]-1); y < y_lo-1; y++)
	{
		// Stap door bytes
		for(uint16_t x = x_lo; x < (x_lo+map[0]); x+=8)
		{
			// Stap door bits en plaats witte pixel als bit hoog is
			for(uint16_t bit = 0; bit <8; bit++) if(map[cursor] & (1 << (7-bit))) setpixel(x+bit, y, VGA_COL_WHITE);
			cursor++;
		}
	}
}

/***************************
Clearscherm: vul het scherm met aangegeven kleur.
(kleur)
(c) Franc van der Bent, aangepast door Jos van Mourik
***************************/
void clearscherm(uint8_t kleur)
{
	for(uint16_t y = 0; y < VGA_DISPLAY_Y; y++)
	{
		for(uint16_t x = 0; x < VGA_DISPLAY_X; x++)
		{
			setpixel(x, y, kleur);
		}
	}
}

/***************************

***************************/
void wacht(uint16_t msecs)
{

}


