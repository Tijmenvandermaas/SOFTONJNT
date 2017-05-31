/***************************************************************
main.c

Democode voor vga_api library.

(c) Jos, Tijmen, Niels 06/2017
***************************************************************/

#include "main.h"
#include "bitmaps.h"

//#define DEBUG

// UART input buffer
char buf[100];
// Argmenten van parseinput
char arguments[8][50];

// Stop uart input in losse strings
uint8_t parseinput(void)
{
	// Uart buffer cursor, argument id
	uint8_t bufcursor = 0;
	uint8_t id = 0;

	// Leeg argument array
	memset(arguments,0,sizeof(arguments));

	while (1)
	{
		// Argument string cursor
		uint8_t argcursor = 0;

		// Check op CR of NULL, stop teken in string
		while(buf[bufcursor]!= 44 && (buf[bufcursor] != 0))
		{
			arguments[id][argcursor] = buf[bufcursor];
			argcursor++;
			bufcursor++;
		}
		// Einde van input bereikt
		if (buf[bufcursor] == 0) break;

		// Ga naar volgende argument, sla komma over
		id++;
		bufcursor++;
	}
	// Aantal gelezen argumenten
	return id;
}

// Verwerk argumenten, stuur API functies aan, geef api return value terug
uint16_t parseoutput(void)
{
	uint16_t r;
	switch(arguments[0][0])
	{
		case 'l':
			r=lijn(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), atoi(&arguments[3][0]), (239-atoi(&arguments[4][0])), atoi(&arguments[5][0]), parsecolor(&arguments[6][0]));
			break;
		case 'e':
			r=ellips(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), atoi(&arguments[3][0]), atoi(&arguments[4][0]), 1, parsecolor(&arguments[5][0]), 1);
			break;
		case 'r':
			r=rechthoek(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), atoi(&arguments[3][0]), (239-atoi(&arguments[4][0])), 1, parsecolor(&arguments[5][0]), 1);
			break;
		case 'd':
			r=driehoek(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), atoi(&arguments[3][0]), (239-atoi(&arguments[4][0])), atoi(&arguments[5][0]), (239-atoi(&arguments[6][0])), 1, parsecolor(&arguments[7][0]), 1);
			break;
		case 't':
			r=tekst(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), (&arguments[3][0]), 1, 1, parsecolor(&arguments[4][0]), parsestijl(&arguments[5][0]));
			break;
		case 'b':
			r=bitmap(atoi(&arguments[2][0]), (239-atoi(&arguments[3][0])), parsebitmap(&arguments[1][0]));
			break;
		case 'c':
			r=clearscherm(parsecolor(&arguments[1][0]));
			break;
		case 'w':
			r=wacht(atoi(&arguments[1][0]));
			break;
	}
	return r;
}

// Geef output van return values
void parseargument(uint16_t error)
{
	  if(error == 0) UART_puts ("success!\n");
	  else if(error == 1 || error == 256) UART_puts ("ERROR1 - coordinaten buiten scherm!\n");
	  else if(error == 2) UART_puts ("ERROR2 - te grote parameter!\n");
	  else if(error == 3) UART_puts ("ERROR3 - foutieve parameter!\n");
}

// Kies kleur op basis van input string
uint8_t parsecolor(char* kleur)
{
	if(strcmp("blauw", kleur) == 0) return BLAUW;
	else if(strcmp("lichtblauw", kleur) == 0) return LICHTBLAUW;
	else if(strcmp("groen", kleur) == 0)return GROEN;
	else if(strcmp("lichtgroen", kleur) == 0) return LICHTGROEN;
	else if(strcmp("cyaan", kleur) == 0) return CYAAN;
	else if(strcmp("lichtcyaan", kleur) == 0) return LICHTCYAAN;
	else if(strcmp("rood", kleur) == 0) return ROOD;
	else if(strcmp("lichtrood", kleur) == 0) return LICHTROOD;
	else if(strcmp("magenta", kleur) == 0) return MAGENTA;
	else if(strcmp("lichtmagenta", kleur) == 0) return LICHTMAGENTA;
	else if(strcmp("bruin", kleur) == 0) return BRUIN;
	else if(strcmp("geel", kleur) == 0) return GEEL;
	else if(strcmp("grijs", kleur) == 0) return GRIJS;
	else if(strcmp("wit", kleur) == 0) return WIT;
	else return 0;
}

// Kies stijl op basis van input string
uint8_t parsestijl(char* stijl)
{
	if(strcmp("normaal", stijl) == 0) return 1;
	else if(strcmp("vet", stijl) == 0) return 2;
	else if(strcmp("cursief", stijl) == 0) return 3;
	else return 0;
}

// Kies bitmap op basis van input string
bitmapfile* parsebitmap(char* bitmaps)
{
	if(atoi(bitmaps) == 0) return &pijl_omhoog_60;
	else if(atoi(bitmaps) == 1) return &pijl_omlaag_60;
	else if(atoi(bitmaps) == 2) return &pijl_links_60;
	else if(atoi(bitmaps) == 3) return &pijl_rechts_60;
	else if(atoi(bitmaps) == 4) return &emoji_blij_64;
	else if(atoi(bitmaps) == 5) return &emoji_boos_64;
	else return 0;
}

int main(void)
{
	// Start clocks
	SystemInit();

	// Start VGA
	UB_VGA_Screen_Init();

	// Zet scherm op zwart
	clearscherm(ZWART);

	// Initieer UART
	UART_init();

	UART_puts ("VGA demo Jos-Niels-Tijmen (c)2017\n");

  while(1)
  {
	  // Stop tekens in buffer, echo
	  UART_gets (buf, 1);

	  // Verwerk argumenten
	  uint8_t args = parseinput();

	  // Check of er argumenten zijn, stuur api aan, verwerk return values
	  if(args) parseargument(parseoutput());

	  #ifdef DEBUG
	  // Geef argumenten weer
	  UART_puts ("---args---\n");
	  for(uint8_t i = 0; i <= args; i++)
	  {
		  UART_puts (&(arguments[i][0]));
		  UART_puts ("\n");
	  }
	  #endif
  }
}
