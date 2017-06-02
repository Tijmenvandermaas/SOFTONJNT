/***************************************************************
vga_ui.c

Democode
UI layer voor vga_api library.

(c) Jos van Mourik
***************************************************************/

#include "vga_ui.h"

// #define DEBUG

// UART input buffer
char buf[100];

// Geef output van return values
void parseargument(uint16_t error)
{
	switch(error)
	{
		case 0: io_write("Succes!\n"); break;
		case 1: io_write("ERROR1 - coordinaten buiten scherm!\n"); break;
		case 2: io_write("ERROR2 - te grote parameter!\n"); break;
		case 3: io_write("ERROR3 - foutieve parameter!\n"); break;
	}
}

int main(void)
{
	// Start clocks
	SystemInit();

	// Start VGA en UART
	io_init();

	// Zet scherm op zwart
	clearscherm(ZWART);

	// Klaar om te ontvangen
	io_write("VGA demo Jos-Niels-Tijmen (c)2017\n");

  while(1)
  {
	  // Stop tekens in buffer, echo
	  #ifndef DEBUG
	  io_read(buf);
	  #endif

	  // Debug zonder uart
	  #ifdef DEBUG
	  strcpy(buf, "tekst,10,10,Hello World,1,wit,vet");
	  #endif

	  // Verwerk uart input, check of er argumenten zijn, stuur api aan, verwerk return values
	  if(parseinput(&buf[0])) parseargument(parseoutput());
  }
}
