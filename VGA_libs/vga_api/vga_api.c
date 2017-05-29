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
#include "stm32_ub_vga_screen.h"

/***************************

***************************/

void tekst(uint16_t x_lo, uint16_t y_lo, uint8_t tekst[100], uint8_t font,  uint8_t grootte,  uint8_t kleur,  uint8_t stijl)

{
	//varibelen waarin de huidig beschreven coordinaten worden opgeslagen
	uint16_t xwrite;
	uint16_t ywrite;
	//variabelen nodig voor het schrijven op meerdere regels
	uint16_t regelplus = 0;
	uint8_t xmin = 0;
	//check voor aantal tekens dat opgestuurd is
	uint16_t size= strlen(tekst);
	//de standaardgrootte van een teken
	const uint16_t hoog = 12;
	const uint16_t breed = 8;


	for(uint8_t i = 0; i<size ;i++)
	{
		//check om te kijken of er naar de volgende regel gegaan moet worden
		if(x_lo+breed*grootte*(i+1) >= 320+grootte*breed*xmin){regelplus++; xmin = i;}
		// Start bitmap data in array
		uint16_t cursor = hoog * tekenbepaling(tekst[i]);

		// Bereken startpunt ten opzichte van linksonden
		for(uint16_t y = (y_lo-hoog*grootte-1); y < y_lo-1; y+= grootte)
		{
			//Zet een aantal keer dezelfde bitline onder elkaar gelijk aan grootte
			for(uint16_t j =0; j < grootte ; j++)
			{
				// Stap door bits van het hexadecimale getal
				for(uint16_t bit = 0; bit <8; bit++)
				{
					//Zet een aantal keer dezelfde bit naast elkaar gelijk aan grootte
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
						if(tekens[cursor] & (1 << (8-bit))) setpixel(xwrite, ywrite, kleur);
					}
				}
			}
			cursor++;
		}
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

	// Success
	return 0;
}

/***************************

***************************/
uint8_t driehoek(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint16_t x_3, uint16_t y_3, uint8_t dikte, uint8_t kleur, bool gevuld)
{
	lijn(x_1,y_1,x_2,y_2,dikte,kleur); //Print de drie lijnen waaruit de driehoek bestaat.
	lijn(x_1,y_1,x_3,y_3,dikte,kleur);
	lijn(x_2,y_2,x_3,y_3,dikte,kleur);

	// Success
	return 0;
}

/***************************
Setpixel: verander pixel van kleur.
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
Readpixel: geef de waarde pixel terug.
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
*****************q**********/
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
wacht: wacht een aantal milliseconden
(msec)
(c) Tijmen van der Maas
***************************/
uint8_t wacht(uint16_t msecs)
{
	uint16_t tel = 0;
	
	//hysync duurt 1/16 milliseconde 
	msecs = msecs*16;		
	
	//in deze loop blijven totdat de teller de ingegeven msec waarde heeft bereikt
	while(tel<msecs)
	{
		if (VGA.hsync_cnt == 500 )
			tel++;
	}

	// Success
	return 0;
}

uint8_t tekenbepaling(uint8_t teken)
{
	uint8_t tekencode;
	switch(teken)
	{
	case ' ': tekencode = 0;  break;
	case '!': tekencode = 1;  break;
	case '"': tekencode = 2;  break;
	case '#': tekencode = 3;  break;
	case '$': tekencode = 4;  break;
	case '%': tekencode = 5;  break;
	case '&': tekencode = 6;  break;
//	case ''': tekencode = 7;  break; // appelstrof?? lukt niet
	case '(': tekencode = 8;  break;
	case ')': tekencode = 9;  break;
	case '*': tekencode = 10; break;
	case '+': tekencode = 11; break;
	case ',': tekencode = 12; break;
	case '-': tekencode = 13; break;
	case '.': tekencode = 14; break;
	case '/': tekencode = 15; break;
	case '0': tekencode = 16; break;
	case '1': tekencode = 17; break;
	case '2': tekencode = 18; break;
	case '3': tekencode = 19; break;
	case '4': tekencode = 20; break;
	case '5': tekencode = 21; break;
	case '6': tekencode = 22; break;
	case '7': tekencode = 23; break;
	case '8': tekencode = 24; break;
	case '9': tekencode = 25; break;
	case ':': tekencode = 26; break;
	case ';': tekencode = 27; break;
	case '<': tekencode = 28; break;
	case '=': tekencode = 29; break;
	case '>': tekencode = 30; break;
	case '?': tekencode = 31; break;
	case '@': tekencode = 32; break;
	case 'A': tekencode = 33; break;
	case 'B': tekencode = 34; break;
	case 'C': tekencode = 35; break;
	case 'D': tekencode = 36; break;
	case 'E': tekencode = 37; break;
	case 'F': tekencode = 38; break;
	case 'G': tekencode = 39; break;
	case 'H': tekencode = 40; break;
	case 'I': tekencode = 41; break;
	case 'J': tekencode = 42; break;
	case 'K': tekencode = 43; break;
	case 'L': tekencode = 44; break;
	case 'M': tekencode = 45; break;
	case 'N': tekencode = 46; break;
	case 'O': tekencode = 47; break;
	case 'P': tekencode = 48; break;
	case 'Q': tekencode = 49; break;
	case 'R': tekencode = 50; break;
	case 'S': tekencode = 51; break;
	case 'T': tekencode = 52; break;
	case 'U': tekencode = 53; break;
	case 'V': tekencode = 54; break;
	case 'W': tekencode = 55; break;
	case 'X': tekencode = 56; break;
	case 'Y': tekencode = 57; break;
	case 'Z': tekencode = 58; break;
	case '[': tekencode = 59; break;
//	case '/': tekencode = 60; break; //backslash lukt niet
	case ']': tekencode = 61; break;
	case '^': tekencode = 62; break;
	case '_': tekencode = 63; break;
	case '`': tekencode = 64; break;
	case 'a': tekencode = 65; break;
	case 'b': tekencode = 66; break;
	case 'c': tekencode = 67; break;
	case 'd': tekencode = 68; break;
	case 'e': tekencode = 69; break;
	case 'f': tekencode = 70; break;
	case 'g': tekencode = 71; break;
	case 'h': tekencode = 72; break;
	case 'i': tekencode = 73; break;
	case 'j': tekencode = 74; break;
	case 'k': tekencode = 75; break;
	case 'l': tekencode = 76; break;
	case 'm': tekencode = 77; break;
	case 'n': tekencode = 78; break;
	case 'o': tekencode = 79; break;
	case 'p': tekencode = 80; break;
	case 'q': tekencode = 81; break;
	case 'r': tekencode = 82; break;
	case 's': tekencode = 83; break;
	case 't': tekencode = 84; break;
	case 'u': tekencode = 85; break;
	case 'v': tekencode = 86; break;
	case 'w': tekencode = 87; break;
	case 'x': tekencode = 88; break;
	case 'y': tekencode = 89; break;
	case 'z': tekencode = 90; break;
	case '{': tekencode = 91; break;
	case '|': tekencode = 92; break;
	case '}': tekencode = 93; break;
	case '~': tekencode = 94; break;
	}

return tekencode;
}
/***************************
Font bitmaps
***************************/
const char tekens[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // <Space> 0
0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x00,0x00, // !		1
0x00,0x28,0x50,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // "		2
0x00,0x00,0x28,0x28,0xFC,0x28,0x50,0xFC,0x50,0x50,0x00,0x00, // #		3
0x00,0x20,0x78,0xA8,0xA0,0x60,0x30,0x28,0xA8,0xF0,0x20,0x00, // $		4
0x00,0x00,0x48,0xA8,0xB0,0x50,0x28,0x34,0x54,0x48,0x00,0x00, // %		5
0x00,0x00,0x20,0x50,0x50,0x78,0xA8,0xA8,0x90,0x6C,0x00,0x00, // &		6
0x00,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '		7
0x00,0x04,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x04,0x00, // (		8
0x00,0x40,0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x40,0x00, // )		9
0x00,0x00,0x00,0x20,0xA8,0x70,0x70,0xA8,0x20,0x00,0x00,0x00, // *		10
0x00,0x00,0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x00,0x00,0x00, // +		11
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x80, // ,		12
0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00, // -		13
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00, // .		14
0x00,0x08,0x10,0x10,0x10,0x20,0x20,0x40,0x40,0x40,0x80,0x00, // /		15
0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00, // 0		16
0x00,0x00,0x20,0x60,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // 1		17
0x00,0x00,0x70,0x88,0x88,0x10,0x20,0x40,0x80,0xF8,0x00,0x00, // 2		18
0x00,0x00,0x70,0x88,0x08,0x30,0x08,0x08,0x88,0x70,0x00,0x00, // 3		19
0x00,0x00,0x10,0x30,0x50,0x50,0x90,0x78,0x10,0x18,0x00,0x00, // 4		20
0x00,0x00,0xF8,0x80,0x80,0xF0,0x08,0x08,0x88,0x70,0x00,0x00, // 5		21
0x00,0x00,0x70,0x90,0x80,0xF0,0x88,0x88,0x88,0x70,0x00,0x00, // 6		22
0x00,0x00,0xF8,0x90,0x10,0x20,0x20,0x20,0x20,0x20,0x00,0x00, // 7		23
0x00,0x00,0x70,0x88,0x88,0x70,0x88,0x88,0x88,0x70,0x00,0x00, // 8		24
0x00,0x00,0x70,0x88,0x88,0x88,0x78,0x08,0x48,0x70,0x00,0x00, // 9		25
0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x20,0x00,0x00, // :		26
0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x20,0x00, // ;		27
0x00,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x00,0x00, // <		28
0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0x00,0x00, // =		29
0x00,0x40,0x20,0x10,0x08,0x04,0x08,0x10,0x20,0x40,0x00,0x00, // >		30
0x00,0x00,0x70,0x88,0x88,0x10,0x20,0x20,0x00,0x20,0x00,0x00, // ?		31
0x00,0x00,0x70,0x88,0x98,0xA8,0xA8,0xB8,0x80,0x78,0x00,0x00, // @		32
0x00,0x00,0x20,0x20,0x30,0x50,0x50,0x78,0x48,0xCC,0x00,0x00, // A		33
0x00,0x00,0xF0,0x48,0x48,0x70,0x48,0x48,0x48,0xF0,0x00,0x00, // B		34
0x00,0x00,0x78,0x88,0x80,0x80,0x80,0x80,0x88,0x70,0x00,0x00, // C		35
0x00,0x00,0xF0,0x48,0x48,0x48,0x48,0x48,0x48,0xF0,0x00,0x00, // D		36
0x00,0x00,0xF8,0x48,0x50,0x70,0x50,0x40,0x48,0xF8,0x00,0x00, // E		37
0x00,0x00,0xF8,0x48,0x50,0x70,0x50,0x40,0x40,0xE0,0x00,0x00, // F		38
0x00,0x00,0x38,0x48,0x80,0x80,0x9C,0x88,0x48,0x30,0x00,0x00, // G		39
0x00,0x00,0xCC,0x48,0x48,0x78,0x48,0x48,0x48,0xCC,0x00,0x00, // H		40
0x00,0x00,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00, // I		41
0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x90,0xE0,0x00, // J		42
0x00,0x00,0xEC,0x48,0x50,0x60,0x50,0x50,0x48,0xEC,0x00,0x00, // K		43
0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x44,0xFC,0x00,0x00, // L		44
0x00,0x00,0xD8,0xD8,0xD8,0xD8,0xA8,0xA8,0xA8,0xA8,0x00,0x00, // M		45
0x00,0x00,0xDC,0x48,0x68,0x68,0x58,0x58,0x48,0xE8,0x00,0x00, // N		46
0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00, // O		47
0x00,0x00,0xF0,0x48,0x48,0x70,0x40,0x40,0x40,0xE0,0x00,0x00, // P		48
0x00,0x00,0x70,0x88,0x88,0x88,0x88,0xE8,0x98,0x70,0x18,0x00, // Q		49
0x00,0x00,0xF0,0x48,0x48,0x70,0x50,0x48,0x48,0xEC,0x00,0x00, // R		50
0x00,0x00,0x78,0x88,0x80,0x60,0x10,0x08,0x88,0xF0,0x00,0x00, // S		51
0x00,0x00,0xF8,0xA8,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // T		52
0x00,0x00,0xCC,0x48,0x48,0x48,0x48,0x48,0x48,0x30,0x00,0x00, // U		53
0x00,0x00,0xCC,0x48,0x48,0x50,0x50,0x30,0x20,0x20,0x00,0x00, // V		54
0x00,0x00,0xA8,0xA8,0xA8,0x70,0x50,0x50,0x50,0x50,0x00,0x00, // W		55
0x00,0x00,0xD8,0x50,0x50,0x20,0x20,0x50,0x50,0xD8,0x00,0x00, // X		56
0x00,0x00,0xD8,0x50,0x50,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // Y		57
0x00,0x00,0xF8,0x90,0x10,0x20,0x20,0x40,0x48,0xF8,0x00,0x00, // Z		58
0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x38,0x00, // [		59
0x00,0x40,0x40,0x40,0x20,0x20,0x10,0x10,0x10,0x08,0x00,0x00, // <Backslash>		60
0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x70,0x00, // ]		61
0x00,0x20,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ^		62
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC, // _		63
0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '		64
0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x38,0x48,0x3C,0x00,0x00, // a		65
0x00,0x00,0xC0,0x40,0x40,0x70,0x48,0x48,0x48,0x70,0x00,0x00, // b		66
0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x40,0x40,0x38,0x00,0x00, // c		67
0x00,0x00,0x18,0x08,0x08,0x38,0x48,0x48,0x48,0x3C,0x00,0x00, // d		68
0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x78,0x40,0x38,0x00,0x00, // e		69
0x00,0x00,0x1C,0x20,0x20,0x78,0x20,0x20,0x20,0x78,0x00,0x00, // f		70
0x00,0x00,0x00,0x00,0x00,0x3C,0x48,0x30,0x40,0x78,0x44,0x38, // g		71
0x00,0x00,0xC0,0x40,0x40,0x70,0x48,0x48,0x48,0xEC,0x00,0x00, // h		72
0x00,0x00,0x20,0x00,0x00,0x60,0x20,0x20,0x20,0x70,0x00,0x00, // i		73
0x00,0x00,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0xE0, // j		74
0x00,0x00,0xC0,0x40,0x40,0x5C,0x50,0x70,0x48,0xEC,0x00,0x00, // k		75
0x00,0x00,0xE0,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00, // l		76
0x00,0x00,0x00,0x00,0x00,0xF0,0xA8,0xA8,0xA8,0xA8,0x00,0x00, // m		77
0x00,0x00,0x00,0x00,0x00,0xF0,0x48,0x48,0x48,0xEC,0x00,0x00, // n		78
0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x48,0x48,0x30,0x00,0x00, // o		79
0x00,0x00,0x00,0x00,0x00,0xF0,0x48,0x48,0x48,0x70,0x40,0xE0, // p		80
0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x48,0x48,0x38,0x08,0x1C, // q		81
0x00,0x00,0x00,0x00,0x00,0xD8,0x60,0x40,0x40,0xE0,0x00,0x00, // r		82
0x00,0x00,0x00,0x00,0x00,0x78,0x40,0x30,0x08,0x78,0x00,0x00, // s		83
0x00,0x00,0x00,0x20,0x20,0x70,0x20,0x20,0x20,0x18,0x00,0x00, // t		84
0x00,0x00,0x00,0x00,0x00,0xD8,0x48,0x48,0x48,0x3C,0x00,0x00, // u		85
0x00,0x00,0x00,0x00,0x00,0xEC,0x48,0x50,0x30,0x20,0x00,0x00, // v		86
0x00,0x00,0x00,0x00,0x00,0xA8,0xA8,0x70,0x50,0x50,0x00,0x00, // w		87
0x00,0x00,0x00,0x00,0x00,0xD8,0x50,0x20,0x50,0xD8,0x00,0x00, // x		88
0x00,0x00,0x00,0x00,0x00,0xEC,0x48,0x50,0x30,0x20,0x20,0xC0, // y		89
0x00,0x00,0x00,0x00,0x00,0x78,0x10,0x20,0x20,0x78,0x00,0x00, // z		90
0x00,0x18,0x10,0x10,0x10,0x20,0x10,0x10,0x10,0x10,0x18,0x00, // {		91
0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10, // |		92
0x00,0x60,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x60,0x00, // }		93
0x40,0xA4,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ~		94
};
