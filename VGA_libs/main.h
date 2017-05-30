/***************************************************************
main.h

Democode voor vga_api library.

(c) Jos, Tijmen, Niels 06/2017
***************************************************************/

//--------------------------------------------------------------
#ifndef __STM32F4_UB_MAIN_H
#define __STM32F4_UB_MAIN_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32_ub_vga_screen.h"
#include "vga_api.h"
#include "uart.h"

//--------------------------------------------------------------
#endif // __STM32F4_UB_MAIN_H

//--------------------------------------------------------------
// Function prototypes
//--------------------------------------------------------------
uint8_t parsecolor(char* kleur);
uint8_t parseoutput(void);
uint8_t parseinput(void);
uint8_t parsestijl(char* stijl);
bitmapfile* parsebitmap(char* bitmaps);
