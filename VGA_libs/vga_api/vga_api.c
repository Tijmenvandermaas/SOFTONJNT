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

void tekst(uint16_t x_lo, uint16_t y_lo, uint8_t tekst[100], uint8_t font,  uint8_t grootte,  uint8_t kleur,  uint8_t stijl)

{
	const uint16_t hoog = 12;
	const uint16_t breed = 8;

	// Start bitmap data in array
	uint16_t cursor = 2 * hoog;

	// Bereken startpunt ten opzichte van linksonder
	for(uint16_t y = (y_lo-hoog-1); y < y_lo-1; y++)
	{
		// Stap door bits en plaats pixel als bit hoog is
		for(uint16_t bit = 0; bit <8; bit++) {if(tekens[cursor] & (1 << (7-bit))){ setpixel(x_lo+bit, y, kleur);}}
		cursor++;
	}
}

/***************************
lijn: teken een lijn.
(x_r, y_r, x_l, y_l, dikte, kleur)
(c) Tijmen van der Maas en een beetje Niels van Rein
***************************/
uint8_t lijn(uint16_t x_l, uint16_t y_l, uint16_t x_r, uint16_t y_r, uint8_t dikte, uint8_t kleur)
{

	//error check
	if (x_l>320 || x_l<0 || x_r>320 || x_r<0 || y_l>240 || y_l<0 || y_r>240 || y_r<0)
		return 1;

	if (dikte > 50)
		return 2;

	//initieer waarden
	uint16_t y_rn;
	uint16_t y_ln;
	uint16_t x_rn;
	uint16_t x_ln;
	uint16_t y;
	uint16_t x;
	float rc;
	uint16_t DIKTE = dikte;


	//verticale lijn
	if (x_r == x_l)

	{	//loop voor dikte, meerdere lijnen tekenen
		for(uint16_t i = 0; i <= DIKTE; i++)
		{
			x_l = x_l + 1;
			x_r = x_r + 1;

			y_ln = y_l;
			y_rn = y_r;

			//loop voor dikte, meerdere lijnen tekenen
			for(uint16_t j = 0; j <= DIKTE; j++)
			{
				y_ln = y_ln + 1;
				y_rn = y_rn + 1;

				//schrijfrichting bepalen
				if (y_l >= y_r)

				{	//pixels schrijven
					for(uint16_t k = y_rn; k <= y_ln; k++)
					{
						UB_VGA_SetPixel(x_r,k,kleur);
					}
				}

				//schrijfrichting bepalen
				if (y_l < y_r)

				{	//pixels schrijven
					for(uint16_t k = y_ln; k <= y_rn; k++)
					{
						UB_VGA_SetPixel(x_r,k,kleur);
					}
				}
			}
		}
	}

	//horizontale lijn
	if (y_r == y_l)

	{	//loop voor dikte, meerdere lijnen tekenen
		for(uint16_t i = 0 ; i <= DIKTE; i++)
		{
			x_l = x_l + 1;
			x_r = x_r + 1;

			y_ln = y_l;
			y_rn = y_r;

			//loop voor dikte, meerdere lijnen tekenen
			for(uint16_t j = 0 ; j <= DIKTE; j++)
			{
				y_ln = y_ln + 1;
				y_rn = y_rn + 1;

				x_rn = x_r;
				x_ln = x_l;

				//schrijfrichting bepalen
				if (x_l > x_r)

				{	//pixels schrijven
					for(uint16_t k = x_rn; k <= x_ln; k++)
					{
						UB_VGA_SetPixel(k,y_rn,kleur);
					}
				}

				//schrijfrichting bepalen
				if (x_ln < x_rn)

				{	//pixels schrijven
					for(uint16_t k = x_ln; k <= x_rn; k++)
					{
						UB_VGA_SetPixel(k,y_ln,kleur);
					}
				}
			}
		}
	}

	//schuine lijn
	else
	{
		// richtingscoefficient berekenen
		rc = (float)(y_r-y_l)/(float)(x_r-x_l);

		//loop voor dikte, meerdere lijnen tekenen, x varieeren
		for(uint16_t i = 0; i <= DIKTE; i++)
		{
			x_l = x_l + 1;
			x_r = x_r + 1;

			y_ln = y_l;
			y_rn = y_r;

			//loop voor dikte, meerdere lijnen tekenen, y varieeren
			for(uint16_t j = 0; j <= DIKTE; j++)
			{
				y_ln = y_ln + 1;
				y_rn = y_rn + 1;

				//schrijfrichting bepalen kwadrant 1
				if(x_l<x_r && y_ln<y_rn)
				{
					//bepalen of y=f(x) of x=f(y) moet worden gebruikt
					if (rc <= 1 && rc >= -1)
					{
						// y bepalen vanuit x met y=f(x) en pixel schrijven
						for(uint16_t k = x_l; k <= x_r; k++)
						{
							y = rc * (k - x_l) + y_ln;
							UB_VGA_SetPixel(k,y,kleur);
						}
					}
					else
					{
						// x bepalen vanuit y met x=f(y) en pixel schrijven
						for(uint16_t k = y_ln; k <= y_rn; k++)
						{
							x =  ((float)(k - y_ln)/(rc))+ x_l;
							UB_VGA_SetPixel(x,k,kleur);
						}
					}
				}

				//schrijfrichting bepalen kwadrant 2
				if(x_l>x_r && y_ln<y_rn)
				{
					//bepalen of y=f(x) of x=f(y) moet worden gebruikt
					if (rc <= 1 && rc >= -1)
					{
						// y bepalen vanuit x met y=f(x) en pixel schrijven
						for(uint16_t k = x_r; k <= x_l; k++)
						{
							y = rc * (k - x_l) + y_ln;
							UB_VGA_SetPixel(k,y,kleur);
						}
					}
					else
					{
						// x bepalen vanuit y met x=f(y) en pixel schrijven
						for(uint16_t k = y_ln; k <= y_rn; k++)
						{
							x =  ((float)(k - y_ln)/(rc))+ x_l;
							UB_VGA_SetPixel(x,k,kleur);
						}
					}
				}

				//schrijfrichting bepalen kwadrant 3
				if(x_l>x_r && y_ln>y_rn)
				{
					//bepalen of y=f(x) of x=f(y) moet worden gebruikt
					if (rc <= 1 && rc >= -1)
					{
						// y bepalen vanuit x met y=f(x) en pixel schrijven
						for(uint16_t k = x_r; k <= x_l; k++)
						{
							y = rc * (k - x_l) + y_ln;
							UB_VGA_SetPixel(k,y,kleur);
						}
					}
					else
					{
						// x bepalen vanuit y met x=f(y) en pixel schrijven
						for(uint16_t k = y_rn; k <= y_ln; k++)
						{
							x =  ((float)(k - y_ln)/(rc))+ x_l;
							UB_VGA_SetPixel(x,k,kleur);
						}
					}
				}

				//schrijfrichting bepalen kwadrant 4
				if(x_l<x_r && y_ln>y_rn)
				{
					//bepalen of y=f(x) of x=f(y) moet worden gebruikt
					if (rc <= 1 && rc >= -1)
					{
						// y bepalen vanuit x met y=f(x) en pixel schrijven
						for(uint16_t k = x_l; k <= x_r; k++)
						{
							y = rc * (k - x_l) + y_ln;
							UB_VGA_SetPixel(k,y,kleur);
						}
					}
					else
					{
						// x bepalen vanuit y met x=f(y) en pixel schrijven
						for(uint16_t k = y_rn; k <= y_ln; k++)
						{
							x =  ((float)(k - y_ln)/(rc))+ x_l;
							UB_VGA_SetPixel(x,k,kleur);
						}
					}
				}
			}
		}
	}
	//succes
	return 0;
}

/***************************
elips: teken een ellips.
(x_mp, y_mp, radius_x, radius_y, dikte, kleur, gevuld)
(c) Tijmen van der Maas
***************************/
uint8_t ellips(uint16_t x_mp, uint16_t y_mp, uint16_t radius_x, uint16_t radius_y, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	//errors
	if(x_mp<1  ||y_mp<1  ||radius_x<1  ||radius_y<1||
	   x_mp>319||y_mp>239||radius_x>320||radius_y>240)
		return 1;

	if ((radius_x >= radius_y)&& (dikte >radius_x/(radius_x/radius_y)))
		return 2;

	if ((radius_x < radius_y) && (dikte >radius_y/(radius_y/radius_x)))
		return 2;

	//inititaliseer variabelen
	int32_t x, y, p;
	uint16_t x_mpn, y_mpn;

	// check of de ellips gevuld moet zijn
	if (gevuld == true )
	{
		// zo ja, dikte aanpassen zodat de ellips gevuld wordt
		if (radius_x >= radius_y)
			dikte = radius_x/(radius_x/radius_y);

		if (radius_x < radius_y)
			dikte = radius_y/(radius_y/radius_x);
	}

	// op basis van dikte meerdere vullende ellipsen tekenen
	for(uint16_t i = 0; i < dikte; i++)
	{
		radius_x = radius_x - 1;
		radius_y = radius_y - 1;

		// middelpunt voor vullende ellipsen 4 keer iets laten afwijken
		for (uint16_t j = 0; j < 4; j++)
		{
			//middelpunt iets laten afwijken
			if (dikte>1)
			{
				if (j==0)
				{
					x_mpn = x_mp -1;
					y_mpn = y_mp;
				}
				if (j==1)
				{
					x_mpn = x_mp;
					y_mpn = y_mp -1;
				}

				if (j==2)
				{
					y_mpn = y_mp;
					x_mpn = x_mp +1;
				}

				if (j==3)
				{
					x_mpn = x_mp;
					y_mpn = y_mp +1;
				}
			}

			// als de ellips dikte 1 is hoeven er geen meerdere elipsen getekend te worden
			else
			{
				x_mpn = x_mp;
				y_mpn = y_mp;
				j=4;
			}

			// hieronder magische ellipscode van het internet http://www.pracspedia.com/CG/midpointellipse.html
			x=0;
			y=radius_y;
			p=(radius_y*radius_y)-(radius_x*radius_x*radius_y)+((radius_x*radius_x)/4);
			while((2*x*radius_y*radius_y)<(2*y*radius_x*radius_x))
			{
				UB_VGA_SetPixel(x_mpn+x,y_mpn-y,kleur);
				UB_VGA_SetPixel(x_mpn-x,y_mpn+y,kleur);
				UB_VGA_SetPixel(x_mpn+x,y_mpn+y,kleur);
				UB_VGA_SetPixel(x_mpn-x,y_mpn-y,kleur);

				if(p<0)
				{
					x=x+1;
					p=p+(2*radius_y*radius_y*x)+(radius_y*radius_y);
				}
				else
				{
					x=x+1;
					y=y-1;
					p=p+(2*radius_y*radius_y*x+radius_y*radius_y)-(2*radius_x*radius_x*y);
				}
			}
			p=((float)x+0.5)*((float)x+0.5)*radius_y*radius_y+(y-1)*(y-1)*radius_x*radius_x-radius_x*radius_x*radius_y*radius_y;
			while(y>=0)
			{
				UB_VGA_SetPixel(x_mpn+x,y_mpn-y,kleur);
				UB_VGA_SetPixel(x_mpn-x,y_mpn+y,kleur);
				UB_VGA_SetPixel(x_mpn+x,y_mpn+y,kleur);
				UB_VGA_SetPixel(x_mpn-x,y_mpn-y,kleur);
				if(p>0)
				{
					y=y-1; p=p-(2*radius_x*radius_x*y)+(radius_x*radius_x);
				}
				else
				{
					y=y-1;
					x=x+1;
					p=p+(2*radius_y*radius_y*x)-(2*radius_x*radius_x*y)-(radius_x*radius_x);
				}
			}
		}
	}
	//succes
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

