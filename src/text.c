#include "text.h"

/*#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <debug.h>
#include <fileioc.h>*/
#include <fontlibc.h>

/*#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>*/

#include <math.h>
/*#include <string.h>
#include <ctype.h>*/

#include "fonts/fonts.h"

#include "main.h"

const uint8_t LEFT_JUSTIFIED   = 0;
const uint8_t CENTER_JUSTIFIED = 1;
const uint8_t RIGHT_JUSTIFIED  = 2;
const uint8_t TOP_ALIGNED      = 0;
const uint8_t MIDDLE_ALIGNED   = 1;
const uint8_t BOTTOM_ALIGNED   = 2;

void initFont() {
	fontlib_SetFont(test_font, 0);
    fontlib_SetLineSpacing(2, 2);
    fontlib_SetColors(COLOR_FONT, COLOR_BG);
}

void drawString(char* string, uint8_t x, uint8_t y, int8_t line, uint8_t justification, uint8_t alignment) {
	uint8_t cx = x;
	uint8_t cy = y + fontlib_GetCurrentFontHeight() * line;
	
	if(justification == LEFT_JUSTIFIED) {}
	else if(justification == CENTER_JUSTIFIED) {cx -= fontlib_GetStringWidth(string) / 2;}
	else if(justification == RIGHT_JUSTIFIED) {cx -= fontlib_GetStringWidth(string);}
	
	if(alignment == TOP_ALIGNED) {}
	else if(alignment == MIDDLE_ALIGNED) {cy -= fontlib_GetCurrentFontHeight() / 2;}
	else if(alignment == BOTTOM_ALIGNED) {cy -= fontlib_GetCurrentFontHeight();}
	
	fontlib_SetWindow(cx, cy, fontlib_GetStringWidth(string), fontlib_GetCurrentFontHeight());
	fontlib_SetCursorPosition(cx, cy);
	
	fontlib_DrawString(string);
}
void drawUInt(uint8_t string, uint8_t x, uint8_t y, int8_t line, uint8_t justification, uint8_t alignment) {
	uint8_t cx = x;
	uint8_t cy = y + fontlib_GetCurrentFontHeight() * line;
	uint8_t stringWidth = 0;
	uint8_t i;
	uint8_t temp;
	
	for(i = 0; i < floor(log(string)) + 1; i++) {
		temp = (uint8_t)(string / pow(10, i)) % 10;
		stringWidth += fontlib_GetGlyphWidth('0' + temp) / 2;
	}
	
	if(justification == LEFT_JUSTIFIED) {}
	else if(justification == CENTER_JUSTIFIED) {cx -= stringWidth / 2;}
	else if(justification == RIGHT_JUSTIFIED) {cx -= stringWidth;}
	
	if(alignment == TOP_ALIGNED) {}
	else if(alignment == MIDDLE_ALIGNED) {cy -= fontlib_GetCurrentFontHeight() / 2;}
	else if(alignment == BOTTOM_ALIGNED) {cy -= fontlib_GetCurrentFontHeight();}
	
	fontlib_SetWindow(cx, cy, stringWidth, fontlib_GetCurrentFontHeight());
	fontlib_SetCursorPosition(cx, cy);
	
	fontlib_DrawUInt(string, 1);
}
void drawULong(uint32_t string, uint8_t x, uint8_t y, int8_t line, uint8_t justification, uint8_t alignment) {
	uint8_t cx = x;
	uint8_t cy = y + fontlib_GetCurrentFontHeight() * line;
	uint8_t stringWidth = 0;
	uint8_t i;
	uint32_t temp;
	
	for(i = 0; i < floor(log(string)) + 1; i++) {
		temp = (uint32_t)(string / pow(10, i)) % 10;
		stringWidth += fontlib_GetGlyphWidth('0' + temp) / 2;
	}
	
	if(justification == LEFT_JUSTIFIED) {}
	else if(justification == CENTER_JUSTIFIED) {cx -= stringWidth / 2;}
	else if(justification == RIGHT_JUSTIFIED) {cx -= stringWidth;}
	
	if(alignment == TOP_ALIGNED) {}
	else if(alignment == MIDDLE_ALIGNED) {cy -= fontlib_GetCurrentFontHeight() / 2;}
	else if(alignment == BOTTOM_ALIGNED) {cy -= fontlib_GetCurrentFontHeight();}
	
	fontlib_SetWindow(cx, cy, stringWidth, fontlib_GetCurrentFontHeight());
	fontlib_SetCursorPosition(cx, cy);
	
	fontlib_DrawUInt(string, 1);
}