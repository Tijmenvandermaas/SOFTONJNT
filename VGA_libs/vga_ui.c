/***************************************************************
vga_ui.c

Democode
UI layer voor vga_api library.

(c) Jos van Mourik
***************************************************************/

#include "vga_ui.h"

//#define DEBUG

// UART input buffer
char buf[100];

// Geef output van return values
void parseargument(uint16_t error)
{
	  if(error == 0) UART_puts ("success!\n");
	  else if(error == 1 || error == 256) UART_puts ("ERROR1 - coordinaten buiten scherm!\n");
	  else if(error == 2) UART_puts ("ERROR2 - te grote parameter!\n");
	  else if(error == 3) UART_puts ("ERROR3 - foutieve parameter!\n");
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
	  #ifndef DEBUG
	  UART_gets (buf, 1);
	  #endif

	  //Debug zonder uart
	  #ifdef DEBUG
	  strcpy(buf, "driehoek,10,10,20,20,30,15,rood");
	  #endif

	  // Verwerk uart input, check of er argumenten zijn, stuur api aan, verwerk return values
	  if(parseinput(&buf[0])) parseargument(parseoutput());

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
