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
	//Bereken richtingscoefficient
	int8_t DIKTE = dikte;
	float rc = (float)(y_r-y_l)/(float)(x_r-x_l);
	int x_ln;
	int x_rn;
	int y_ln;
	int yo;
	int yn;
	int j,i,m,n;

	for(j = (DIKTE *-1) ; j <= DIKTE; j++)       // nieuwe y's op basis van dikte
	{
		y_ln = y_l +j;
		yo = y_ln;
		for(n = (DIKTE * -1); n <= DIKTE; n++)  // nieuwe x's op basis van dikte
		{
			x_ln = x_l +n;
			x_rn = x_r +n;
		}
			for(i = x_ln; i <= x_rn; i++) 		// lijn schrijven op basis van de x-waarden van de lijn
			{

				yn = rc * (i - x_ln) + y_ln;    // y = richtingscoefficient * (x-waarde - x-offset) + y-offset

				if ((yn != (yo+1)) || (yn != (yo-1)) || (yn != yo) & (yn>yo)) // check of er gaten vallen bij y-waarden op de lijn
				{
					for(m = 1; m <= ((yn-yo)-1); m++)						  //de gaten opvullen
					{
						UB_VGA_SetPixel(i,(yo+m),kleur);
					}
				}

				if ((yn != (yo+1)) || (yn != (yo-1)) || (yn != yo) & (yn<yo)) // check of er gaten vallen bij y-waarden op de lijn
				{
					for(m = 1; m <= ((yo-yn)-1); m++)						  //de gaten opvullen
					{
						UB_VGA_SetPixel(i,(yo-m),kleur);
					}
				}

				yo = yn;
				UB_VGA_SetPixel(i,yo,kleur);								  // pixel schrijven bij nieuwe x en y
			}
	}
}

/***************************

***************************/
void ellips(uint16_t x_mp, uint16_t y_mp, uint16_t radius_x, uint16_t radius_y, uint8_t dikte, uint8_t kleur, bool gevuld)
{

}

/***************************

***************************/
void rechthoek(uint16_t x_lo, uint16_t y_lo, uint16_t x_rb, uint16_t y_rb, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	// Teken horizontale lijnen
	for( uint16_t i = x_lo; i < x_rb; i++ )
	  {
		  VGA_RAM1[(y_rb*(VGA_DISPLAY_X+1))+i]=kleur;
		  VGA_RAM1[(y_lo*(VGA_DISPLAY_X+1))+i]=kleur;
	  }

	//Teken verticale lijnen
	for( uint16_t j = y_rb; j < (y_lo+1); j++ )
	  {
		  VGA_RAM1[(j*(VGA_DISPLAY_X+1))+x_lo]=kleur;
		  VGA_RAM1[(j*(VGA_DISPLAY_X+1))+x_rb]=kleur;
	  }
}

/***************************

***************************/
void driehoek(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint16_t x_3, uint16_t y_3, uint8_t dikte, uint8_t kleur, bool gevuld)
{

}

/***************************

***************************/
void setpixel(uint16_t x, uint16_t y, uint8_t kleur)
{

}

/***************************

***************************/
uint8_t readpixel(uint16_t x, uint16_t y)
{

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


