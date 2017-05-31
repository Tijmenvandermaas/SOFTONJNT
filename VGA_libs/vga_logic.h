/***************************************************************
vga_logic.h

Democode
Logic layer voor vga_api library.

(c) Jos van Mourik
***************************************************************/

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "vga_ui.h"

//--------------------------------------------------------------
// Function prototypes
//--------------------------------------------------------------
uint8_t parseinput(char* buf);
uint16_t parseoutput(void);
uint8_t parsecolor(char* kleur);
uint8_t parsestijl(char* stijl);
bitmapfile* parsebitmap(char* bitmaps);
