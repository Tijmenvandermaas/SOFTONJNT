/***************************************************************
vga_io.c

Democode
IO layer voor vga_api library.

(c) Jos van Mourik en een beetje Niels van Rijn
***************************************************************/
#include "vga_io.h"

// Initieer UART en VGA driver
void io_init(void)
{
	UART_init();
	UB_VGA_Screen_Init();
}

// Lees UART uit
void io_read(char *buf)
{
	UART_gets(buf, 1);
}

// Schrijf op UART
void io_write(char *buf)
{
	UART_puts(buf);
}
