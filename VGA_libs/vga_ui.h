/***************************************************************
vga_ui.h

Democode
UI layer voor vga_api library.

(c) Jos van Mourik
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
#include "vga_logic.h"

//--------------------------------------------------------------
#endif // __STM32F4_UB_MAIN_H

//--------------------------------------------------------------
// Function prototypes
//--------------------------------------------------------------
void parseargument(uint16_t error);
