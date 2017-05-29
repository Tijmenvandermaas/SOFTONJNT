/***************************************************************
main.c

Democode voor vga_api library.

(c) Jos, Tijmen, Niels 05/2017
***************************************************************/

#include "main.h"
#include "bitmaps.h"

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


	// Tekst demo
	tekst(10, 50, "Hallo mensjes, mijn naam is Niels en ik ben cool", 100, 2, BLAUW, 100);


	UART_puts ("READY\n");

	// UART input buffer
	char buf[100];

	// Argmenten van parseinput
	char arguments[10][50];

	// Zet uart receive in losse strings
	uint8_t parseinput(void)
	{
		// Uart buffer cursor
		uint8_t bufcursor = 0;

		// Argument id
		uint8_t id = 0;

		// Legen argumenten
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

			id++;
			bufcursor++;
		}
		// Aantal gelezen argumenten
		return id;
	}




  while(1)
  {
	  // Stop tekens in buffer, echo
	  UART_gets (buf, 0);
	  UART_puts (buf);
	  UART_puts ("\n");

	  // Verwerk argumenten
	  uint8_t args = parseinput();

	  // Geef argumenten weer
	  UART_puts ("---args---\n");
	  for(uint8_t i = 0; i <= args; i++)
	  {
		  UART_puts (&(arguments[i][0]));
		  UART_puts ("\n");
	  }
  }
}


