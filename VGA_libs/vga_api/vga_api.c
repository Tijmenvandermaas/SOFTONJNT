/***************************************************************
vga_api.h

Return values:
0 - succes
1 - buiten scherm! (256 bij getpixel)
2 - dikte/invoer te groot!
3 - foutieve invoer!

HU Software Ontwikkeling.
(c) Jos, Tijmen, Niels 06/2017
***************************************************************/

/***************************
Includes
***************************/
#include "vga_api.h"
#include "fonts.h"

/** @file vga_api.c
Functie	      | agrument 1    | agrument 2    | agrument 3    | agrument 4    | agrument 5    | agrument 6    | agrument 7    | agrument 8    | agrument 9  
------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | -------------
Tekst	      | x_lo          | y_lo          | tekst         | font          | grootte       | kleur         | stijl         | n.v.t.	      | n.v.t.	     		
Lijn	      | x_l           | y_l           | x_r           | y_r           | dikte         | kleur         | n.v.t.	      | n.v.t.	      | n.v.t.        
Ellips        | x_mp	      | y_mp	      | raius_x	      | radius_y      | dikte	      | kleur	      | gevuld	      | n.v.t.	      | n.v.t.	     
Rechthoek     | x_lo	      | y_lo	      | x_rb          | y_rb          | dikte         | kleur	      | gevuld	      | n.v.t.	      | n.v.t.	     
Driehoek      | x_1	      | y_1	      | x_2	      | y_2	      | x_3	      | y_3	      | dikte	      | kleur	      | gevuld 
Setpixel      | x	      | y	      | kleur	      | n.v.t.	      | n.v.t.	      | n.v.t.        | n.v.t.	      | n.v.t.	      | n.v.t.        
Readpixel     | x	      | y             | n.v.t.	      | n.v.t.	      | n.v.t.        | n.v.t.	      | n.v.t.	      | n.v.t.        | n.v.t.
Bitmap        | x_lo	      | y_lo	      | bitmap	      | n.v.t.	      | n.v.t.	      | n.v.t.        | n.v.t.	      | n.v.t.	      | n.v.t.        
Clearscherm   | kleur	      | n.v.t.	      | n.v.t.	      | n.v.t.        | n.v.t.	      | n.v.t.	      | n.v.t.        | n.v.t.	      | n.v.t.      
Wacht         | msecs	      | n.v.t.	      | n.v.t.	      | n.v.t.        | n.v.t.	      | n.v.t.	      | n.v.t.        | n.v.t.	      | n.v.t.      
*/



/***************************
tekst: zet tekst op scherm
(x_lo, y_lo, tekst[100], font, grootte, kleur, stijl)
(c) Niels van Rijn
***************************/

/*!	een functie die een tekst schrijft op een specifieke plek met een variabele grootte, lettertype, stijl en kleur
	\param x is een unsigned 16 bit integer argument, dit is de x waarde van de positie
	\param y is een unsigned 16 bit integer argument, dit is de y waarde van de positie
	\param tekst is een unsigned 8 bit integer buffer argument, dit is de tekst
	\param font is een unsigned 8 bit integer argument, dit is het lettertype
	\param grootte is een unsigned 8 bit integer argument, dit bepaalt de grootte van de tekst
	\param kleur is een unsigned 8 bit integer argument, dit bepaalt de kleur van de tekst
	\param stijl is een unsigned 8 bit integer argument, dit bepaalt de stijl van de tekst
	\return 0  = succes
	\return 1  = buiten scherm
	\return 2  = tekst te groot voor het scherm.
	\return 3  = invoer fout bij font, grootte of stijl
*/

uint8_t tekst(uint16_t x_lo, uint16_t y_lo, char* tekst, uint8_t font, uint8_t grootte, uint8_t kleur, uint8_t stijl)
{
	// Error checks
	// Buiten grenzen van het scherm
	if (x_lo>=VGA_DISPLAY_X || y_lo>=VGA_DISPLAY_Y) return 1;
	// Font, grootte of stijl hebben een ongeldige invoer.
	if ((font != FONT_1 && font != FONT_2) || (stijl != REGULAR && stijl != BOLD && stijl != OBLIQUE) || grootte > 10 ) return 3;

	// Variabelen waarin de huidig beschreven coordinaten[i] worden opgeslagen
	uint16_t xwrite;
	uint16_t ywrite;
	// Variabelen nodig voor het schrijven op meerdere regels
	uint16_t regelplus = 0;
	uint8_t xmin = 0;
	// Variabelen nodig voor het uitlezen van de tekst
	uint8_t tekstvalue;
	uint16_t cursor;
	// Check het aantal tekens dat opgestuurd is
	uint16_t size = strlen((const char*)tekst);
	// Standaardgrootte van een teken
	const uint16_t hoog = 12;
	const uint16_t breed = 7;

	for(uint8_t i = 0; i<size ;i++)
	{
		// Check om te kijken of er naar de volgende regel gegaan moet worden
		if(x_lo+breed*grootte*(i+1) >= VGA_DISPLAY_X+grootte*breed*xmin){regelplus++; xmin = i;}

		// De ASCI waarde van het huidig geschreven teken opslaan.
		tekstvalue = (tekst[i]);
		// Spatie is nummer 0x20 op de ASCI tabel en nummer 0x0 in de bitmap. Vanaf daar wordt de ASCI lijst gevolgd tot en met 0x7E
		cursor = hoog * (tekstvalue - 0x20);

		// Bereken startpunt ten opzichte van linksonder
		for(uint16_t y = (y_lo-hoog*grootte-1); y < y_lo-1; y+=grootte)
		{
			// Zet een aantal keer dezelfde bitline onder elkaar gelijk aan grootte
			for(uint16_t j =0; j < grootte; j++)
			{
				// Stap door bits van het hexadecimale getal
				for(uint16_t bit = 0; bit <8; bit++)
				{
					// Zet een aantal keer dezelfde bit naast elkaar gelijk aan grootte
					for(uint16_t k = 0; k< grootte; k++)
					{
						//berekenen op welke plek de pixels berekend moeten worden
						/* xwrite = x_lo+bit*grootte-k+-grootte*breed*xmin;
						 * +x_lo					: De opgegeven startpositie.
						 * +bit*grootte-k			: Elke bit wordt grootte aantal keer naast elkaar gezet.
						 * +breed*grootte*i 		: Bepalen van de beginwaarde van elk volgend teken
						 * -grootte*breed*xmin		: De x waarde wordt weer op x_lo gezet als er na een volgende regel gegaan wordt.
						 *
						 * ywrite = y+j+regelplus*grootte*hoog;
						 * +y						: De opgegeven startpositie opgehoogd na elke regel van bits
						 * +j						: Elke bit wordt grootte aantal keer onder elkaar gezet.
						 * +regelplus*grootte*hoog	: Als er naar de volgende regel gegaan wordt, gaat de y waarde een teken-hoogte omhoog
						 */
						xwrite = x_lo+bit*grootte-k+breed*grootte*i-grootte*breed*xmin;
						ywrite = y+j+regelplus*grootte*hoog;

						// Check of ywrite te groot is
						if (ywrite >= VGA_DISPLAY_Y) return 2;

						// Bepalen welk font te gebruiken
						if(font == 1)
						{
							// Bepalen welke stijl te gebruiken (Regular, Bold, Oblique)
							switch(stijl)
							{
								case 1: if(VCR_OSD_Mono_Regular[cursor] & (1 << (8-bit))) setpixel(xwrite, ywrite, kleur); break;
								case 2: if(VCR_OSD_Mono_Bold[cursor] & (1 << (8-bit))) setpixel(xwrite, ywrite, kleur); break;
								case 3: if(VCR_OSD_Mono_Oblique[cursor] & (1 << (8-bit))) setpixel(xwrite, ywrite, kleur); break;
							}
						}
						else if(font == 2)
						{
							// Bepalen welke stijl te gebruiken (Regular, Bold, Oblique)
							switch(stijl)
							{
								case 1: if(F04b03_Regular [cursor] & (1 << (8-bit))) setpixel(xwrite, ywrite, kleur); break;
								case 2: if(F04b03_Bold[cursor] & (1 << (8-bit))) setpixel(xwrite, ywrite, kleur); break;
								case 3: if(F04b03_Oblique[cursor] & (1 << (8-bit))) setpixel(xwrite, ywrite, kleur); break;
							}
						}
					}
				}
			}
			cursor++;
		}
	}
	// Succes
	return 0;
}

/***************************
lijn: teken een lijn.
(x_r, y_r, x_l, y_l, dikte, kleur)
(c) Tijmen van der Maas en Niels van Rijn
***************************/

/*!	een functie die een lijn tekent tussen 2 punten met een variabele dikte en kleur
	\param x_r is een unsigned 16 bit integer argument, dit is de rechter x waarde
	\param y_r is een unsigned 16 bit integer argument, dit is de rechter y waarde
	\param x_l is een unsigned 16 bit integer argument, dit is de linker x waarde
	\param y_l is een unsigned 16 bit integer argument, dit is de linker y waarde
	\param dikte is een unsigned 8 bit integer argument, dit bepaalt de dikte van de lijn
	\param kleur is een unsigned 8 bit integer argument, dit bepaalt de kleur van de lijn
	\return 0  = succes
	\return 1  = buiten scherm
	\return 2  = dikte te groot
*/
uint8_t lijn(uint16_t x_l, uint16_t y_l, uint16_t x_r, uint16_t y_r, uint8_t dikte, uint8_t kleur)
{
	// Error check
	if (x_l>=VGA_DISPLAY_X || x_r>=VGA_DISPLAY_X || y_l>=VGA_DISPLAY_Y || y_r>=VGA_DISPLAY_Y) return 1;
	if (dikte > 50) return 2;

	// Initieer waarden
	uint16_t y_rn = y_r;
	uint16_t y_ln = y_l;
	uint16_t x_rn = x_r;
	uint16_t x_ln = x_l;
	uint16_t y;
	uint16_t x;
	uint16_t x_begin;
	uint16_t x_end;
	uint16_t y_begin;
	uint16_t y_end;

	float rc;

	// Loop voor dikte, meerdere lijnen tekenen
	for(uint16_t i = 1; i <= dikte +1; i++)
	{
		x_ln++;
		x_rn++;
		y_ln = y_l;
		y_rn = y_r;

		// Loop voor dikte, meerdere lijnen tekenen
		for(uint16_t j = 1; j <= dikte +1; j++)
		{
			y_ln++;
			y_rn++;

			// Verticale lijn
			if (x_r == x_l)
			{
				// Schrijfrichting bepalen
				if (y_l >= y_r)
				{	// Pixels schrijven
					y_begin = y_rn;
					y_end = y_ln;
				}
				else if(y_l < y_r)
				{
					y_begin = y_ln;
					y_end = y_rn;
				}
				for(uint16_t k = y_begin; k <= y_end; k++)
				{
					setpixel(x_rn,k,kleur);
				}
			}
			// Horizontale lijn
			else if (y_r == y_l)
			{
				// Schrijfrichting bepalen
				if (x_l > x_r)
				{	// Pixels schrijven
					x_begin = x_rn;
					x_end = x_ln;
				}
				else if (x_r > x_l)
				{
					x_begin = x_ln;
					x_end = x_rn;
				}
				for(uint16_t k = x_begin; k <= x_end; k++)
				{
					setpixel(k,y_rn,kleur);
				}
			}
			//Schuine lijnen
			else
			{
				// Richtingscoefficient berekenen
				rc = (float)(y_r-y_l)/(float)(x_r-x_l);

				// Schrijfrichting bepalen kwadrant 1
				if(x_l<x_r && y_ln<y_rn)
				{
					x_begin = x_ln;
					x_end = x_rn;
					y_begin = y_ln;
					y_end = y_rn;
				}
				// Schrijfrichting bepalen kwadrant 2
				else if(x_l>x_r && y_ln<y_rn)
				{
					x_begin = x_rn;
					x_end = x_ln;
					y_begin = y_ln;
					y_end = y_rn;
				}
				// Schrijfrichting bepalen kwadrant 3
				else if(x_l>x_r && y_ln>y_rn)
				{
					x_begin = x_rn;
					x_end = x_ln;
					y_begin = y_rn;
					y_end = y_ln;
				}
				// Schrijfrichting bepalen kwadrant 4
				else if(x_l<x_r && y_ln>y_rn)
				{
					x_begin = x_ln;
					x_end = x_rn;
					y_begin = y_rn;
					y_end = y_ln;
				}

				if (rc <= 1 && rc >= -1)
				{
					// y bepalen vanuit x met y=f(x) en pixel schrijven
					for(uint16_t k = x_begin; k <= x_end; k++)
					{
						y = rc * (k - x_ln) + y_ln;
						setpixel(k,y,kleur);
					}
				}
				else
				{
					// x bepalen vanuit y met x=f(y) en pixel schrijven
					for(uint16_t k = y_begin; k <= y_end; k++)
					{
						x =  ((float)(k - y_ln)/(rc))+ x_ln;
						setpixel(x,k,kleur);
					}
				}
			}
		}
	}
	// Succes
	return 0;
}

/***************************
elips: teken een ellips.
(x_mp, y_mp, radius_x, radius_y, dikte, kleur, gevuld)
(c) Tijmen van der Maas
***************************/

/*!	een functie die een ellips tekent om een middelpunt met een variabele y-radius, x-radius, dikte, kleur en vulling
	\param x_mp is een unsigned 16 bit integer argument, dit is de x waarde van het middelpunt
	\param y_mp is een unsigned 16 bit integer argument, dit is de y waarde van het middelpunt
	\param radius_x is een unsigned 16 bit integer argument, dit is de grootte van de x-radius
	\param radius_y is een unsigned 16 bit integer argument, dit is de grootte van de y-radius
	\param dikte is een unsigned 8 bit integer argument, dit bepaalt de dikte van de ellips
	\param kleur is een unsigned 8 bit integer argument, dit bepaalt de kleur van de ellips
	\param gevuld is een boolean, deze bepaalt of de ellips wel of niet gevuld is
	\return 0  = succes
	\return 1  = buiten scherm
	\return 2  = dikte te groot
*/

uint8_t ellips(uint16_t x_mp, uint16_t y_mp, uint16_t radius_x, uint16_t radius_y, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	// Errors
	if(x_mp ==0  || y_mp ==0  || radius_x ==0  || radius_y ==0 ||
	   x_mp >= VGA_DISPLAY_X || y_mp >= VGA_DISPLAY_Y || radius_x >= VGA_DISPLAY_X || radius_y >= VGA_DISPLAY_Y ||
	   x_mp + (radius_x) >= VGA_DISPLAY_X || x_mp - (radius_x) <= 0 ||
	   y_mp + (radius_y) >= VGA_DISPLAY_Y || x_mp - (radius_y) <= 0) return 1;

	if (((radius_x >= radius_y)&& (dikte >radius_x/(radius_x/radius_y))) ||
	    ((radius_x < radius_y) && (dikte >radius_y/(radius_y/radius_x)))) return 2;

	// Inititaliseer variabelen
	int32_t x, y, p;
	uint16_t x_mpn, y_mpn;

	// Check of de ellips gevuld moet zijn
	if (gevuld)
	{
		// Zo ja, dikte aanpassen zodat de ellips gevuld wordt
		if (radius_x >= radius_y)
			dikte = radius_y;

		if (radius_x < radius_y)
			dikte = radius_x;
	}

	// Op basis van dikte meerdere vullende ellipsen tekenen
	for(uint16_t i = 0; i < dikte; i++)
	{
		radius_x = radius_x - 1;
		radius_y = radius_y - 1;

		// Middelpunt voor vullende ellipsen 4 keer iets laten afwijken
		for (uint16_t j = 0; j < 4; j++)
		{
			// Middelpunt iets laten afwijken
			if (dikte>1)
			{
				switch(j)
				{
					case 0:
						x_mpn = x_mp -1;
						y_mpn = y_mp;
						break;
					case 1:
						x_mpn = x_mp;
						y_mpn = y_mp -1;
						break;
					case 2:
						y_mpn = y_mp;
						x_mpn = x_mp +1;
						break;
					case 3:
						x_mpn = x_mp;
						y_mpn = y_mp +1;
						break;
				}
			}

			// Als de ellips dikte 1 is hoeven er geen meerdere elipsen getekend te worden
			else
			{
				x_mpn = x_mp;
				y_mpn = y_mp;
				j=4;
			}

			// Hieronder ellipscode van internet http://www.pracspedia.com/CG/midpointellipse.html
			// Author: Darshan Gajara
			x=0;
			y=radius_y;
			p=(radius_y*radius_y)-(radius_x*radius_x*radius_y)+((radius_x*radius_x)/4);
			while((2*x*radius_y*radius_y)<(2*y*radius_x*radius_x))
			{
				setpixel(x_mpn+x,y_mpn-y,kleur);
				setpixel(x_mpn-x,y_mpn+y,kleur);
				setpixel(x_mpn+x,y_mpn+y,kleur);
				setpixel(x_mpn-x,y_mpn-y,kleur);

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
				setpixel(x_mpn+x,y_mpn-y,kleur);
				setpixel(x_mpn-x,y_mpn+y,kleur);
				setpixel(x_mpn+x,y_mpn+y,kleur);
				setpixel(x_mpn-x,y_mpn-y,kleur);
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
	// Succes
	return 0;
}

/***************************
rechthoek: teken een rechthoek.
(x_lo, y_lo, x_rb, y_rb, dikte, kleur, gevuld)
(c) Jos van Mourik
***************************/

/*!	een functie die een rechthoek tekent op basis van 2 punten met een variabele dikte, kleur en vulling
	\param x_lo is een unsigned 16 bit integer argument, dit is de x waarde van linksonder
	\param y_lo is een unsigned 16 bit integer argument, dit is de y waarde van linksonder
	\param x_rb is een unsigned 16 bit integer argument, dit is de x waarde van rechtsboven
	\param y_rb is een unsigned 16 bit integer argument, dit is de y waarde van rechtsboven
	\param dikte is een unsigned 8 bit integer argument, dit bepaalt de dikte van de rechthoek
	\param kleur is een unsigned 8 bit integer argument, dit bepaalt de kleur van de rechthoek
	\param gevuld is een boolean, deze bepaalt of de rechthoek wel of niet gevuld is
	\return 0  = succes
	\return 1  = buiten scherm
	\return 2  = dikte te groot
*/

uint8_t rechthoek(uint16_t x_lo, uint16_t y_lo, uint16_t x_rb, uint16_t y_rb, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	// Tekenen buiten scherm voorkomen
	if(x_rb>=VGA_DISPLAY_X || y_lo>=VGA_DISPLAY_Y) return 1;

	// Te grote dikte voorkomen
	if(dikte > ((y_lo-y_rb)/2)) return 2;

	// Gevulde rechthoek of overflow lijndikte
	if(gevuld || dikte >= ((x_rb-x_lo)/2) || dikte == ((y_lo-y_rb)/2))
	{
		// Verticale waarden
		for (uint16_t y = y_rb; y < (y_lo+1); y++)
		{
			// Horizontale waarden
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
	// Succes
	return 0;
}

/***************************
driehoek: teken een driehoek.
(x_1, y_1, x_2, y_2, x_3, y_3, dikte, kleur, gevuld)
(c) Niels van Rijn en Tijmen van der Maas
***************************/

/*!	een functie die een driehoek tekent op basis van 3 punten met een variabele dikte, kleur en vulling
	\param x_1 is een unsigned 16 bit integer argument, dit is de x waarde van punt 1
	\param y_1 is een unsigned 16 bit integer argument, dit is de y waarde van punt 1
	\param x_2 is een unsigned 16 bit integer argument, dit is de x waarde van punt 2
	\param y_2 is een unsigned 16 bit integer argument, dit is de y waarde van punt 2
	\param x_3 is een unsigned 16 bit integer argument, dit is de x waarde van punt 3
	\param y_3 is een unsigned 16 bit integer argument, dit is de y waarde van punt 3
	\param dikte is een unsigned 8 bit integer argument, dit bepaalt de dikte van de driehoek
	\param kleur is een unsigned 8 bit integer argument, dit bepaalt de kleur van de driehoek
	\param gevuld is een boolean, deze bepaalt of de driehoek wel of niet gevuld is
	\return 0  = succes
	\return 1  = buiten scherm
	\return 2  = dikte te groot
*/

uint8_t driehoek(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint16_t x_3, uint16_t y_3, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	// Error check
	if (x_1 >= VGA_DISPLAY_X || x_2>=VGA_DISPLAY_X || x_3>=VGA_DISPLAY_X || y_1>=VGA_DISPLAY_Y || y_2>=VGA_DISPLAY_Y|| y_3>=VGA_DISPLAY_Y) return 1;
	if (dikte > 50) return 2;

	if(gevuld == 0)
	{
		uint8_t error1 = lijn(x_1,y_1,x_2,y_2,1,kleur); //Print de drie lijnen waaruit de driehoek bestaat.
		uint8_t error2 = lijn(x_1,y_1,x_3,y_3,1,kleur);
		uint8_t error3 = lijn(x_2,y_2,x_3,y_3,1,kleur);

		//als de lijnfuncties een error geven kopieer deze error
		if(error1) return error1;
		if(error2) return error2;
		if(error3) return error3;
	}
	else
	{
		uint16_t coordinaten[VGA_DISPLAY_Y][2];
		memset(coordinaten,0,sizeof(coordinaten));
		uint8_t vullen = 0;

		// Initieer waarden
		uint16_t x_ln;
		uint16_t y_ln;
		uint16_t x_rn;
		uint16_t y_rn;
		uint16_t y;
		uint16_t x;
		uint16_t x_begin;
		uint16_t x_end;
		uint16_t y_begin;
		uint16_t y_end;
		float rc;
		for(uint8_t i = 0; i<3; i++)
		{
			//uint16_t x_l, uint16_t y_l, uint16_t x_r, uint16_t y_r
			switch (i)
			{
				case 0: x_ln = x_1; y_ln = y_1; x_rn = x_2; y_rn = y_2; break;
				case 1: x_ln = x_1; y_ln = y_1; x_rn = x_3; y_rn = y_3; break;
				case 2: x_ln = x_2; y_ln = y_2; x_rn = x_3; y_rn = y_3; break;
			}

			// Verticale lijn
			if (x_rn == x_ln)
			{
				// Schrijfrichting bepalen
				if (y_ln >= y_rn)
				{	// Pixels schrijven
					y_begin = y_rn;
					y_end = y_ln;
				}
				else if(y_ln < y_rn)
				{
					y_begin = y_ln;
					y_end = y_rn;
				}
				for(uint16_t k = y_begin; k <= y_end; k++)
				{
					if(x_rn < coordinaten[k][0] || coordinaten[k][0] == 0) coordinaten[k][0] = x_rn;
					if(x_rn > coordinaten[k][1]) coordinaten[k][1] = x_rn;
				}
			}
			// Horizontale lijn
			else if (y_rn == y_ln)
			{
				// Schrijfrichting bepalen
				if (x_ln > x_rn)
				{
					x_begin = x_rn;
					x_end = x_ln;
				}
				else if (x_rn > x_ln)
				{
					x_begin = x_ln;
					x_end = x_rn;
				}
				for(uint16_t k = x_begin; k <= x_end; k++)
				{
					if(k < coordinaten[y_rn][0] || coordinaten[y_rn][0] == 0) coordinaten[y_rn][0] = k;
					if(k > coordinaten[y_rn][1]) coordinaten[y_rn][1] = k;
				}
			}
			//Schuine lijnen
			else
			{
				// Richtingscoefficient berekenen
				rc = (float)(y_rn-y_ln)/(float)(x_rn-x_ln);
				// Schrijfrichting bepalen kwadrant 1
				if(x_ln<x_rn && y_ln<y_rn)
				{
					x_begin = x_ln;
					x_end = x_rn;
					y_begin = y_ln;
					y_end = y_rn;
				}
				// Schrijfrichting bepalen kwadrant 2
				else if(x_ln>x_rn && y_ln<y_rn)
				{
					x_begin = x_rn;
					x_end = x_ln;
					y_begin = y_ln;
					y_end = y_rn;
				}
				// Schrijfrichting bepalen kwadrant 3
				else if(x_ln>x_rn && y_ln>y_rn)
				{
					x_begin = x_rn;
					x_end = x_ln;
					y_begin = y_rn;
					y_end = y_ln;
				}
				// Schrijfrichting bepalen kwadrant 4
				else if(x_ln<x_rn && y_ln>y_rn)
				{
					x_begin = x_ln;
					x_end = x_rn;
					y_begin = y_rn;
					y_end = y_ln;
				}
				if (rc <= 1 && rc >= -1)
				{
					// y bepalen vanuit x met y=f(x) en pixel schrijven
					for(uint16_t k = x_begin; k <= x_end; k++)
					{
						y = rc * (k - x_ln) + y_ln;
						if(k < coordinaten[y][0] || coordinaten[y][0] == 0) coordinaten[y][0] = k;
						if(k > coordinaten[y][1]) coordinaten[y][1] = k;
					}
				}
				else
				{
					// x bepalen vanuit y met x=f(y) en pixel schrijven
					for(uint16_t k = y_begin; k <= y_end; k++)
					{
						x =  ((float)(k - y_ln)/(rc))+ x_ln;
						if(x < coordinaten[k][0] || coordinaten[k][0] == 0) coordinaten[k][0] = x;
						if(x > coordinaten[k][1]) coordinaten[k][1] = x;
					}
				}
			}
		}
		//loop door het hele scherm
		for(y = 0; y<VGA_DISPLAY_Y; y++)
		{
			for(x = 0; x<VGA_DISPLAY_X; x++)
			{
				//check om te kijken of er op deze horiontale lijn iets staat
				if(coordinaten[y][0] && coordinaten[y][1])
				{
					//begin met vullen bij de eerste lijn van de driehoek todat de tweede lijn tegengekomen wordt.
					if(coordinaten[y][0] == x) {vullen = 1; setpixel(x,y,kleur);}
					if(vullen) setpixel(x,y,kleur);
					if(coordinaten[y][1] == x){ vullen = 0;}
				}
			}
		vullen = 0;
		}
	}
	// Succes
	return 0;
}

/***************************
setpixel: verander pixel van kleur.
(x, y, kleur)
(c) Franc van der Bent, aangepast door Jos van Mourik
***************************/

/*!	een functie die een pixel tekent op basis een x en y coördinaat met een variabele kleur
	\param x is een unsigned 16 bit integer argument, dit is de x waarde het punt
	\param y is een unsigned 16 bit integer argument, dit is de y waarde het punt
	\param kleur is een unsigned 8 bit integer argument, dit bepaalt de kleur van het punt
	\return 0  = succes
	\return 1  = buiten scherm
*/

uint8_t setpixel(uint16_t x, uint16_t y, uint8_t kleur)
{
	if((x<VGA_DISPLAY_X) && (y<VGA_DISPLAY_Y))
	{
		VGA_RAM1[(y*(VGA_DISPLAY_X+1))+x] = kleur;

		// Succes
		return 0;
	}

	// Tekenen buiten scherm voorkomen
	return 1;
}

/***************************
readpixel: geef de waarde pixel terug.
(x, y)
(c) Jos van Mourik
***************************/

/*!	een functie die een pixel leest op basis een x en y coördinaat
	\param x is een unsigned 16 bit integer argument, dit is de x waarde het punt
	\param y is een unsigned 16 bit integer argument, dit is de y waarde het punt
	\return kleur
	\return 256  = buiten scherm
*/

uint16_t readpixel(uint16_t x, uint16_t y)
{
	if((x<VGA_DISPLAY_X) && (y<VGA_DISPLAY_Y)) return VGA_RAM1[(y*(VGA_DISPLAY_X+1))+x];

	// Lezen buiten scherm voorkomen
	return 256;
}

/***************************
bitmap: 256 kleuren R3G3B2 bitmaps.
(x_lo, y_lo, map)
(c) Jos van Mourik
*****************q**********/

/*!	een functie die een afbeelding tekent op basis een x en y linksonder coördinaat en een bitmap
	\param x is een unsigned 16 bit integer argument, dit is de x linksonder waarde 
	\param y is een unsigned 16 bit integer argument, dit is de y linksonder waarde 
	\param bitmap is een bitmap datastructuur, hierin staat de afbeelding
	\return 0  = succes
	\return 1  = buiten scherm
*/
uint8_t bitmap(uint16_t x_lo, uint16_t y_lo, bitmapfile *bitmap)
{
	// Tekenen buiten scherm voorkomen
	if((x_lo+bitmap->x)>=VGA_DISPLAY_X || y_lo>=VGA_DISPLAY_Y) return 1;
	if(bitmap == 0) return 3;

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
	// Succes
	return 0;
}

/***************************
clearscherm: vul het scherm met aangegeven kleur.
(kleur)
(c) Franc van der Bent, aangepast door Jos van Mourik
***************************/

/*!	een functie die het scherm vult met een kleur
	\param kleur is een unsigned 8 bit integer argument, deze bepaalt de kleur
	\return 0  = succes
*/

uint8_t clearscherm(uint8_t kleur)
{
	for(uint16_t y = 0; y < VGA_DISPLAY_Y; y++)
	{
		for(uint16_t x = 0; x < VGA_DISPLAY_X; x++)
		{
			setpixel(x, y, kleur);
		}
	}
	// Succes
	return 0;
}

/***************************
wacht: wacht een aantal milliseconden
(msec)
(c) Tijmen van der Maas
***************************/

/*!	een functie die het programma een aantal milliseconden laat wachten
	\param msec is een unsigned 16 bit integer argument, dit is de wachtijd in milliseconden
	\return 0  = succes
*/

uint8_t wacht(uint16_t msecs)
{
	// Check voor overflow
	if(msecs >= 65536) return 2;

	uint32_t tel = 0;
	
	// In loop blijven totdat de teller de ingegeven msec waarde heeft bereikt
	while(tel<(msecs*16))
	{
		if (VGA.hsync_cnt == 500 )
			tel++;
	}
	// Succes
	return 0;
}

/*!	een functie die een character vertaald naar zijn numerieke waarde
	\param teken een unsigned 8 bit integer die een character voorstelt
	\return unsigned 8 bit integer met de numerieke waarde van de character
*/

