/***************************************************************
vga_api.h

*****************************************
Return values:
0 - success
1 - buiten scherm! (256 bij getpixel)
2 - dikte te groot!
*****************************************

HU Software Ontwikkeling.
(c) Jos, Tijmen, Niels 05/2017
***************************************************************/

/***************************
Includes
***************************/
#include "vga_api.h"


/***************************

***************************/
//uint8_t tekst(uint16_t x, uint16_t y, uint8_t tekst[100], uint8_t font,  uint8_t grootte,  uint8_t kleur,  uint8_t stijl)
uint8_t tekst(uint16_t x_lo, uint16_t y_lo, char map[], uint8_t letter)
{
	// Start bitmap data in array
	uint16_t cursor = letter * 12 + 4;

	// Bereken startpunt ten opzichte van linksonder
	for(uint16_t y = (y_lo-map[2]-1); y < y_lo-1; y++)
	{
		// Stap door bytes
		for(uint16_t x = x_lo; x < (x_lo+map[0]); x+=8)
		{
			// Stap door bits en plaats witte pixel als bit hoog is
			for(uint16_t bit = 0; bit <8; bit++) {if(map[cursor] & (1 << (7-bit))){ setpixel(x+bit, y, VGA_COL_WHITE);}}
			cursor++;
		}
	}

	// Success
	return 0;
}

/***************************

***************************/
uint8_t lijn(uint16_t x_l, uint16_t y_l, uint16_t x_r, uint16_t y_r, uint8_t dikte, uint8_t kleur)
{
	//Bereken richtingscoefficient

	int y_rn;
	int y_ln;
	int x_rn;
	int x_ln;
	int y;
	int x;
	int j,i,m,n;
	float rc;
	int DIKTE = dikte;



	if (x_r == x_l) 								//verticale lijn
	{
		for(m = 0; m <= DIKTE; m++)
		{
			x_l = x_l + 1;
			x_r = x_r + 1;

			y_ln = y_l;
			y_rn = y_r;

			for(j = 0; j <= DIKTE; j++)
			{
				y_ln = y_ln + 1;
				y_rn = y_rn + 1;

				if (y_l > y_r)
				{
					for(y_rn; y_rn <= y_ln; y_rn++)
					{
						UB_VGA_SetPixel(x_r,y_rn,kleur);
					}
				}

				if (y_l < y_r)
				{
					for(y_ln; y_ln <= y_rn; y_ln++)
					{
						UB_VGA_SetPixel(x_r,y_ln,kleur);
					}
				}
			}
		}
	}

	if (y_r == y_l)									//horizontale lijn
	{
		for(m = 0 ; m <= DIKTE; m++)
		{
			x_l = x_l + 1;
			x_r = x_r + 1;

			y_ln = y_l;
			y_rn = y_r;

			for(j = 0 ; j <= DIKTE; j++)
			{
				y_ln = y_ln + 1;
				y_rn = y_rn + 1;

				x_rn = x_r;
				x_ln = x_l;

				if (x_l > x_r)
				{
					for(x_rn; x_rn <= x_ln; x_rn++)
					{
						UB_VGA_SetPixel(x_rn,y_rn,kleur);
					}
				}

				if (x_ln < x_rn)
				{
					for(x_ln; x_ln <= x_rn; x_ln++)
					{
						UB_VGA_SetPixel(x_ln,y_ln,kleur);
					}
				}
			}
		}
	}
	else												//schuine lijn
	{

		rc = (float)(y_r-y_l)/(float)(x_r-x_l);

		for(m = 0; m <= DIKTE; m++)
		{
			x_l = x_l + 1;
			x_r = x_r + 1;

			y_ln = y_l;
			y_rn = y_r;

			for(j = 0; j <= DIKTE; j++)
			{
				y_ln = y_ln + 1;
				y_rn = y_rn + 1;


				if(x_l<x_r & y_ln<y_rn)
				{
					if (rc <= 1 & rc >= -1)
					{
						for(i = x_l; i <= x_r; i++)
						{
							y = rc * (i - x_l) + y_ln;
							UB_VGA_SetPixel(i,y,kleur);
						}
					}
					else
					{
						for(i = y_ln; i <= y_rn; i++)
						{
							x =  ((float)(i - y_ln)/(rc))+ x_l;
							UB_VGA_SetPixel(x,i,kleur);
						}
					}
				}

				if(x_l>x_r & y_ln<y_rn)
				{
					if (rc <= 1 & rc >= -1)
					{
						for(i = x_r; i <= x_l; i++)
						{
							y = rc * (i - x_l) + y_ln;
							UB_VGA_SetPixel(i,y,kleur);
						}
					}
					else
					{
						for(i = y_ln; i <= y_rn; i++)
						{
							x =  ((float)(i - y_ln)/(rc))+ x_l;
							UB_VGA_SetPixel(x,i,kleur);
						}
					}
				}

				if(x_l>x_r & y_ln>y_rn)
				{
					if (rc <= 1 & rc >= -1)
					{
						for(i = x_r; i <= x_l; i++)
						{
							y = rc * (i - x_l) + y_ln;
							UB_VGA_SetPixel(i,y,kleur);
						}
					}
					else
					{
						for(i = y_rn; i <= y_ln; i++)
						{
							x =  ((float)(i - y_ln)/(rc))+ x_l;
							UB_VGA_SetPixel(x,i,kleur);
						}
					}
				}

				if(x_l<x_r & y_ln>y_rn)
				{
					if (rc <= 1 & rc >= -1)
					{
						for(i = x_l; i <= x_r; i++)
						{
							y = rc * (i - x_l) + y_ln;
							UB_VGA_SetPixel(i,y,kleur);
						}
					}
					else
					{
						for(i = y_rn; i <= y_ln; i++)
						{
							x =  ((float)(i - y_ln)/(rc))+ x_l;
							UB_VGA_SetPixel(x,i,kleur);
						}
					}
				}
			}
		}
	}

	// Success
	return 0;
}

/***************************

***************************/
uint8_t ellips(uint16_t x_mp, uint16_t y_mp, uint16_t radius_x, uint16_t radius_y, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	// Success
	return 0;
}

/***************************
Rechthoek: teken een rechthoek.
(x_lo, y_lo, x_rb, y_rb, dikte, kleur, gevuld)
(c) Jos van Mourik
***************************/
uint8_t rechthoek(uint16_t x_lo, uint16_t y_lo, uint16_t x_rb, uint16_t y_rb, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	// Tekenen buiten scherm voorkomen
	if(x_rb>=VGA_DISPLAY_X || y_lo>=VGA_DISPLAY_Y) return 1;


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

	// Success
	return 0;
}

/***************************

***************************/
uint8_t driehoek(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint16_t x_3, uint16_t y_3, uint8_t dikte, uint8_t kleur)
{
	lijn(x_1,y_1,x_2,y_2,dikte,kleur); //Print de drie lijnen waaruit de driehoek bestaat.
	lijn(x_1,y_1,x_3,y_3,dikte,kleur);
	lijn(x_2,y_2,x_3,y_3,dikte,kleur);

	// Success
	return 0;
}

/***************************
Setpixel: verandert één pixel van kleur.
(x, y, kleur)
(c) Franc van der Bent, aangepast door Jos van Mourik
***************************/
uint8_t setpixel(uint16_t x, uint16_t y, uint8_t kleur)
{
	if((x<VGA_DISPLAY_X) && (y<VGA_DISPLAY_Y))
	{
		VGA_RAM1[(y*(VGA_DISPLAY_X+1))+x] = kleur;

		// Success
		return 0;
	}

	// Tekenen buiten scherm voorkomen
	else return 1;
}

/***************************
Readpixel: geef de waarde van één pixel terug.
(x, y)
(c) Jos van Mourik
***************************/
uint16_t readpixel(uint16_t x, uint16_t y)
{
	if((x<VGA_DISPLAY_X) && (y<VGA_DISPLAY_Y)) return VGA_RAM1[(y*(VGA_DISPLAY_X+1))+x];

	// Lezen buiten scherm voorkomen
	else return 256;
}

/***************************
bitmap: 256 kleuren bitmaps.
(x_lo, y_lo, map)
(c) Jos van Mourik
***************************/
uint8_t bitmap(uint16_t x_lo, uint16_t y_lo, bitmapfile *bitmap)
{
	// Tekenen buiten scherm voorkomen
	if((x_lo+bitmap->x)>=VGA_DISPLAY_X || y_lo>=VGA_DISPLAY_Y) return 1;


	// Startpunt pixel data
	uint32_t cursor = 0;

	// Bereken Y-waarden ten opzichte van onderen
	for(uint16_t y = (y_lo-bitmap->y+1); y < (y_lo+1); y++)
	{
		// Loop door X-waarden
		for(uint16_t x = x_lo; x < (x_lo+bitmap->x); x++)
		{
			setpixel(x, y, bitmap->data[cursor]);
			cursor++;
		}
	}

	// Success
	return 0;
}

/***************************
Clearscherm: vul het scherm met aangegeven kleur.
(kleur)
(c) Franc van der Bent, aangepast door Jos van Mourik
***************************/
uint8_t clearscherm(uint8_t kleur)
{
	for(uint16_t y = 0; y < VGA_DISPLAY_Y; y++)
	{
		for(uint16_t x = 0; x < VGA_DISPLAY_X; x++)
		{
			setpixel(x, y, kleur);
		}
	}

	// Success
	return 0;
}

/***************************

***************************/
uint8_t wacht(uint16_t msecs)
{
	// Success
	return 0;
}

