/***************************************************************
vga_api.h



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
rechthoek functie
(c) Jos van Mourik
***************************/
void rechthoek(uint16_t x_lo, uint16_t y_lo, uint16_t x_rb, uint16_t y_rb, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	if(gevuld)
	{
		// Verticale lijnen vullen
		for (uint16_t j = y_rb; j < (y_lo+1); j++)
		{
			// Horizontale lijnen vullen
			for(uint16_t i = x_lo; i < (x_rb+1); i++)
			{
				  setpixel(i, j, kleur);
			}
		}
	}

	else
	{
		// stappen door lijndikte
		for(uint8_t k = 0; k < dikte; k++)
		{
			// Teken horizontale lijnen
			for(uint16_t i = x_lo; i < (x_rb+1); i++)
			{
				  setpixel(i, (y_rb+k), kleur);
				  setpixel(i, (y_lo-k), kleur);
			}

			//Teken verticale lijnen
			for(uint16_t j = (y_rb+dikte); j < y_lo+1-dikte; j++)
			{
				  setpixel((x_lo+k), j, kleur);
				  setpixel((x_rb-k), j, kleur);
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
setpixel functie: verandert één pixel van kleur.
(c) Jos van Mourik
***************************/
void setpixel(uint16_t x, uint16_t y, uint8_t kleur)
{
	if((x<=VGA_DISPLAY_X) && (y<=VGA_DISPLAY_Y))
	{
		VGA_RAM1[(y*(VGA_DISPLAY_X+1))+x] = kleur;
	}
}

/***************************
readpixel functie: geeft de waarde van één pixel terug.
(c) Jos van Mourik
***************************/
uint8_t readpixel(uint16_t x, uint16_t y)
{
	return VGA_RAM1[(y*(VGA_DISPLAY_X+1))+x];
}

/***************************

***************************/
void bitmap(uint16_t x_lo, uint16_t y_lo, uint8_t map)
{

}

/***************************

***************************/
void clearscherm(uint8_t kleur)
{

}

/***************************

***************************/
void wacht(uint16_t msecs)
{

}


