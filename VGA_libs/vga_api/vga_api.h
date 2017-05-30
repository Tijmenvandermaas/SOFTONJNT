/***************************************************************
vga_api.h


HU Software Ontwikkeling.
(c) Jos, Tijmen, Niels 05/2017
***************************************************************/

/***************************
Includes
***************************/
#include <stdbool.h>
#include "stm32_ub_vga_screen.h"

/***************************
Globale variabelen
***************************/

// Struct voor bitmaps
typedef const struct
{
	uint16_t x;
	uint16_t y;
    char data[];
}bitmapfile;

// Kleuren (R3G3B2)
#define  ZWART			0x00
#define  BLAUW			0x03
#define  LICHTBLAUW		0x0B
#define  GROEN			0x1C
#define  LICHTGROEN		0x5D
#define  CYAAN			0x1F
#define  LICHTCYAAN		0x9B
#define  ROOD			0xE0
#define  LICHTROOD		0xE9
#define  MAGENTA		0xE3
#define  LICHTMAGENTA	0xF3
#define  BRUIN			0x88
#define  GEEL			0xFC
#define  GRIJS			0x92
#define  WIT			0xFF

//Stijlen
#define	 Regular		0x01
#define	 Bold			0x02
#define	 Oblique		0x03

//Fonts
#define	 Font_1			0x01
#define	 Font_2			0x02

//Sizes
#define	 Size_1			0x01
#define	 Size_2			0x02
#define	 Size_3			0x03
#define  Size_4			0x04
#define	 Size_5			0x05
#define  Size_6			0x06
#define	 Size_7			0x07
#define  Size_8			0x08
#define	 Size_9			0x09
#define  Size_10		0x0A

/***************************
Globale functies
***************************/
void tekst(uint16_t x_lo, uint16_t y_lo, uint8_t tekst[100], uint8_t font,  uint8_t grootte,  uint8_t kleur,  uint8_t stijl);
uint8_t lijn(uint16_t x_l, uint16_t y_l, uint16_t x_r, uint16_t y_r, uint8_t dikte, uint8_t kleur);
uint8_t ellips(uint16_t x_mp, uint16_t y_mp, uint16_t radius_x, uint16_t radius_y, uint8_t dikte, uint8_t kleur, bool gevuld);
uint8_t rechthoek(uint16_t x_lo, uint16_t y_lo, uint16_t x_rb, uint16_t y_rb, uint8_t dikte, uint8_t kleur, bool gevuld);
uint8_t driehoek(uint16_t x_1, uint16_t y_1, uint16_t x_2, uint16_t y_2, uint16_t x_3, uint16_t y_3, uint8_t dikte, uint8_t kleur, bool gevuld);
uint8_t setpixel(uint16_t x, uint16_t y, uint8_t kleur);
uint16_t readpixel(uint16_t x, uint16_t y);
uint8_t bitmap(uint16_t x_lo, uint16_t y_lo, bitmapfile *bitmap);
uint8_t clearscherm(uint8_t kleur);
uint8_t wacht(uint16_t msecs);
uint8_t tekenbepaling(uint8_t teken);

