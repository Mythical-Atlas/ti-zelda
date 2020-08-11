#include "menu.h"

/*#include <tice.h>*/
#include <graphx.h>
/*#include <keypadc.h>
#include <debug.h>
#include <fileioc.h>*/
#include <fontlibc.h>

/*#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>*/
#include <stdint.h>
/*#include <stdbool.h>

#include <math.h>
#include <string.h>
#include <ctype.h>*/

#include "main.h"
#include "text.h"
#include "field.h"

uint8_t menuState;
uint8_t menuTimer;
uint8_t menuSelection;

void initMenu() {
	menuState = 0;
	menuTimer = 0;
	menuSelection = 0;
}
void updateMenu() {
	if(menuState == 0) { // PRESS ENTER
		if(keyClear && keyClearReady) {
			keyClearReady = 0;
			running = 0;
		}
		if(keyEnter && keyEnterReady) {
			keyEnterReady = 0;
			menuState = 1;
			menuSelection = 0;
		}
		
		menuTimer++;
		if(menuTimer >= 60) {menuTimer = 0;}
	}
	else if(menuState == 1) { // START | CONTROLS
		if(keyClear && keyClearReady) {
			keyClearReady = 0;
			menuState = 0;
		}
		if(keyEnter && keyEnterReady) {
			keyEnterReady = 0;
			
			if(menuSelection == 0) {menuState = 3;}
			else if(menuSelection == 1) {menuState = 2;}
		}
		
		if(keyUp && keyUpReady) {
			keyUpReady = 0;
			
			if(menuSelection > 0) {menuSelection--;}
			else {menuSelection = 1;}
		}
		if(keyDown && keyDownReady) {
			
			keyUpReady = 0;
			if(menuSelection < 1) {menuSelection++;}
			else {menuSelection = 0;}
		}
	}
	else if(menuState == 2) { // list controls
		if(keyClear && keyClearReady) {
			keyClearReady = 0;
			menuState = 0;
		}
	}
	else if(menuState == 3) {changeState(1);} // return to main menu
}
void drawMenu() {
	gfx_FillScreen(COLOR_BG);
	
	if(menuState == 0) { // PRESS ENTER
		drawString("TETRIS", 160, 0, 0, CENTER_JUSTIFIED, TOP_ALIGNED);
		
		if(menuTimer < 30) {drawString("Press Enter", 160, 120, 0, CENTER_JUSTIFIED, MIDDLE_ALIGNED);}
		
		drawString("Programmed by Ben Correll", 10, 240, 0, LEFT_JUSTIFIED, BOTTOM_ALIGNED);
		drawString("Version 1.0", 310, 240, 0, RIGHT_JUSTIFIED, BOTTOM_ALIGNED);
	}
	else if(menuState == 1) { // START | CONTROLS
		drawString("TETRIS", 160, 0, 0, CENTER_JUSTIFIED, TOP_ALIGNED);
		
		if(menuSelection == 0) {fontlib_SetColors(COLOR_FONT, COLOR_BG);}
		else {fontlib_SetColors(COLOR_FIELD, COLOR_BG);}
		drawString("Start", 160, 120, -1, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
		
		if(menuSelection == 1) {fontlib_SetColors(COLOR_FONT, COLOR_BG);}
		else {fontlib_SetColors(COLOR_FIELD, COLOR_BG);}
		drawString("Controls", 160, 120, 1, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
		
		fontlib_SetColors(COLOR_FONT, COLOR_BG);
		
		drawString("Programmed by Ben Correll", 10, 240, 0, LEFT_JUSTIFIED, BOTTOM_ALIGNED);
		drawString("Version 1.0", 310, 240, 0, RIGHT_JUSTIFIED, BOTTOM_ALIGNED);
	}
	else if(menuState == 2) { // list controls
		drawString("Controls", 160, 0, 0, CENTER_JUSTIFIED, TOP_ALIGNED);
		drawString("Left and right arrows to move", 160, 120, -3, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
		drawString("Down arrow to fast drop", 160, 120, -2, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
		drawString("Up arrow to hard drop", 160, 120, -1, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
		drawString("2nd and mode to rotate", 160, 120, 0, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
		drawString("Del to save", 160, 120, 1, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
		drawString("Press Clear to Return", 160, 240, 0, CENTER_JUSTIFIED, BOTTOM_ALIGNED);
	}
	
	gfx_Blit(gfx_buffer);
}