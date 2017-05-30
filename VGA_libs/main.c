/***************************************************************
main.c

Democode voor vga_api library.

(c) Jos, Tijmen, Niels 05/2017
***************************************************************/

#include "main.h"
#include "bitmaps.h"

// UART input buffer
char buf[100];
// Argmenten van parseinput
char arguments[10][50];

// Stop uart input in losse strings
uint8_t parseinput(void)
{
	// Uart buffer cursor
	uint8_t bufcursor = 0;

	// Argument id
	uint8_t id = 0;

<<<<<<< HEAD
	// Initieer UART
	UART_init();
	UART_INT_init();

/*
	// Rechthoek demo
	rechthoek(0, 239, 319, 0, 10, VGA_COL_WHITE, 0);
	rechthoek(20, 225, 300, 20, 3, VGA_COL_RED, 0);
	rechthoek(25, 220, 100, 25, 1, VGA_COL_BLUE, 1);
	rechthoek(150, 130, 250, 30, 1, VGA_COL_GREEN, 1);
	rechthoek(175, 200, 200, 175, 2, VGA_COL_MAGENTA, 0);
*/

/*
	  // Lijn demo
	  lijn(0, 10, 200, 10, 10, VGA_COL_BLUE);
	  lijn(0, 30, 100, 50, 5, VGA_COL_RED);
	  lijn(0, 100, 200, 50, 1, VGA_COL_GREEN);
	  lijn(50, 200, 100, 100, 20, VGA_COL_YELLOW);
	  lijn(220, 10, 220, 220, 1, VGA_COL_WHITE);
*/


/*
	  // Bitmap demo
	  bitmap(25, 100, &emoji_blij_64);
	  bitmap(100, 100, &emoji_boos_64);
	  bitmap(175, 100, &HU_logo_50);
	  bitmap(25, 200, &pijl_omhoog_60);
	  bitmap(100, 200, &pijl_omlaag_60);
	  bitmap(175, 200, &pijl_links_60);
	  bitmap(250, 200, &pijl_rechts_60);
*/


//	// Kleuren demo
//	lijn(0,10,239,10, 5, BLAUW);
//	lijn(0,20,239,20, 5, LICHTBLAUW);
//	lijn(0,30,239,30, 5, GROEN);
//	lijn(0,40,239,40, 5, LICHTGROEN);
//	lijn(0,50,239,50, 5, ROOD);
//	lijn(0,60,239,60, 5, LICHTROOD);
//	lijn(0,70,239,70, 5, CYAAN);
//	lijn(0,80,239,80, 5, LICHTCYAAN);
//	lijn(0,90,239,90, 5, MAGENTA);
//	lijn(0,100,239,100, 5, LICHTMAGENTA);
//	lijn(0,110,239,110, 5, BRUIN);
//	lijn(0,120,239,120, 5, GEEL);
//	lijn(0,130,239,130, 5, GRIJS);
//	lijn(0,140,239,140, 5, WIT);
=======
	// Legen argumenten
	memset(arguments,0,sizeof(arguments));

	while (1)
	{
		// Argument string cursor
		uint8_t argcursor = 0;
>>>>>>> origin/master

		// Check op CR of NULL, stop teken in string
		while(buf[bufcursor]!= 44 && (buf[bufcursor] != 0))
		{
			arguments[id][argcursor] = buf[bufcursor];
			argcursor++;
			bufcursor++;
		}
		// Einde van input bereikt
		if (buf[bufcursor] == 0) break;

<<<<<<< HEAD
	// Tekst demo
	tekst(10, 50, "Hallo Mensjes, mijn naam is Niels en ik ben cool", Font_1, Size_4 ,BLAUW, Bold);

	// UART Demo
	  UART_putint(1);
	  UART_putint(0);
	  UART_putint(11);
	  UART_putint(0);
	  wacht(500);

	  char string[100];
	  char* stringptr = string;
=======
		id++;
		bufcursor++;
	}
	// Aantal gelezen argumenten
	return id;
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

// Verwerk argumenten en stuur API functies aan.
uint8_t parseoutput(void)
{
	switch(arguments[0][0])
	{
		case 'l':
			lijn(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), atoi(&arguments[3][0]), (239-atoi(&arguments[4][0])), atoi(&arguments[5][0]), parsecolor(&arguments[6][0]));
			break;
		case 'e':
			ellips(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), atoi(&arguments[3][0]), atoi(&arguments[4][0]), 1, parsecolor(&arguments[5][0]), 1);
			break;
		case 'r':
			rechthoek(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), atoi(&arguments[3][0]), (239-atoi(&arguments[4][0])), 1, parsecolor(&arguments[5][0]), 1);
			break;
		case 'd':
			driehoek(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), atoi(&arguments[3][0]), (239-atoi(&arguments[4][0])), atoi(&arguments[5][0]), (239-atoi(&arguments[6][0])), 1, parsecolor(&arguments[7][0]), 1);
			break;
		case 't':
			tekst(atoi(&arguments[1][0]), (239-atoi(&arguments[2][0])), (arguments[3][0]), 1, 1, parsecolor(&arguments[4][0]), parsestijl(&arguments[5][0])); // tekst moet pointer worden
			break;
		case 'b':
			bitmap(atoi(&arguments[2][0]), (239-atoi(&arguments[3][0])), parsebitmap(&arguments[1][0]));
			break;
		case 'c':
			clearscherm(parsecolor(&arguments[1][0]));
			break;
		case 'w':
			wacht(atoi(&arguments[1][0]));
			break;
	}

	return 0;
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
>>>>>>> origin/master

	UART_puts ("VGA demo Jos-Niels-Tijmen (c)2017\n");

  while(1)
  {
<<<<<<< HEAD
	  	  UART_gets (stringptr, 1);
	  	  UART_puts (stringptr);
	  	  UART_puts ("LOOP\n");
	  	  wacht(100);

	  	  /* Rechthoek formaat demo
	  	  for(int i = 0; i <240; i++)
	  	  {
	  		  clearscherm(VGA_COL_BLACK);
	  		  rechthoek(0, 239, i, (239-i), 5, VGA_COL_BLUE, 0);
	  		  for(int j = 0; j <100000; j++);
	  	  }

	  	  // Rechthoek dikte demo
	  	  for (int k = 0; k <76; k++)
	  	  {
	  		  rechthoek(50, 200, 200, 50, k, VGA_COL_CYAN, 0);
	  		  for(int j = 0; j <(100000); j++);
	  	  }

	  	  // Beeld vasthouden
	  	  for(int j = 0; j <(100000000); j++); */
  }
}

=======
	  // Stop tekens in buffer, echo
	  UART_gets (buf, 0);

	  // Echo input
	  UART_puts (buf);
	  UART_puts ("\n");

	  // Verwerk argumenten
	  uint8_t args = parseinput();

	  parseoutput();

	  // Geef argumenten weer
	  UART_puts ("---args---\n");
	  for(uint8_t i = 0; i <= args; i++)
	  {
		  UART_puts (&(arguments[i][0]));
		  UART_puts ("\n");
	  }
  }
}
>>>>>>> origin/master
