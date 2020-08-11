/*

Tetris for the TI-84 Plus CE graphing calculator
Programmed by Ben Correll
Last updated 8-10-2020

*/

#include "main.h"

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include <debug.h>
/*#include <fileioc.h>
#include <fontlibc.h>*/

/*#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <math.h>
#include <string.h>
#include <ctype.h>*/

#include "game.h"
#include "menu.h"
#include "gameOver.h"
#include "text.h"
#include "color.h"

const uint16_t CLOCK_SPEED = 32768;
const uint16_t KHZ = 1000;
const uint8_t FPS = 60;

const uint8_t COLOR_BG    = 0x00;
const uint8_t COLOR_FONT  = 0x02;

uint8_t programState;
bool running;
uint32_t realFPS;

bool keyUp;
bool keyDown;
bool keyLeft;
bool keyRight;
bool key2nd;
bool keyMode;
bool keyDel;
bool keyEnter;
bool keyClear;

bool keyUpReady;
bool keyDownReady;
bool keyLeftReady;
bool keyRightReady;
bool key2ndReady;
bool keyModeReady;
bool keyDelReady;
bool keyEnterReady;
bool keyClearReady;

int main(void) {
	uint32_t elapsed = 0;
	uint32_t begin = 0;
	uint32_t end = 0;
	
	running = 1;
	
	keyUpReady = 0;
	keyDownReady = 0;
	keyLeftReady = 0;
	keyRightReady = 0;
	key2ndReady = 0;
	keyModeReady = 0;
	keyDelReady = 0;
	keyEnterReady = 0;
	keyClearReady = 0;
	
	changeState(0);
	
	timer_Control = TIMER1_DISABLE;
    timer_1_Counter = 0;
    timer_Control = TIMER1_ENABLE | TIMER1_32K | TIMER1_UP;
	realFPS = 0;
	
	gfx_Begin(gfx_8bpp);
	//gfx_SetTransparentColor(0x40);
	gfx_SetPalette(palette, 0xFF, 0);
	gfx_SetDrawBuffer();
	
	initFont();
	
	while(running) {
		timer_1_Counter = 0;
		
		keyUp = 0;
		keyDown = 0;
		keyLeft = 0;
		keyRight = 0;
		key2nd = 0;
		keyMode = 0;
		keyDel = 0;
		keyEnter = 0;
		keyClear = 0;
		
		kb_Scan();
		
		if(kb_Data[7] & kb_Up) {keyUp = 1;}
		if(kb_Data[7] & kb_Down) {keyDown = 1;}
		if(kb_Data[7] & kb_Left) {keyLeft = 1;}
		if(kb_Data[7] & kb_Right) {keyRight = 1;}
		if(kb_Data[1] & kb_2nd) {key2nd = 1;}
		if(kb_Data[1] & kb_Mode) {keyMode = 1;}
		if(kb_Data[1] & kb_Del) {keyDel = 1;}
		if(kb_Data[6] & kb_Enter) {keyEnter = 1;}
		if(kb_Data[6] & kb_Clear) {keyClear = 1;}
		
		if(programState == 0) {updateMenu();}
		else if(programState == 1) {updateGame();}
		else if(programState == 2) {updateGameOver();}
		
		keyUpReady = !keyUp;
		keyDownReady = !keyDown;
		keyLeftReady = !keyLeft;
		keyRightReady = !keyRight;
		key2ndReady = !key2nd;
		keyModeReady = !keyMode;
		keyDelReady = !keyDel;
		keyEnterReady = !keyEnter;
		keyClearReady = !keyClear;
		
		if(programState == 0) {drawMenu();}
		else if(programState == 1) {drawGame();}
		else if(programState == 2) {drawGameOver();}
		
		if(atomic_load_increasing_32(&timer_1_Counter) < (CLOCK_SPEED / FPS)) {delay((uint16_t)((CLOCK_SPEED / FPS - atomic_load_increasing_32(&timer_1_Counter)) * KHZ / CLOCK_SPEED));}
		realFPS = CLOCK_SPEED / atomic_load_increasing_32(&timer_1_Counter);
	}
	
	gfx_End();
	
	return(0);
}

void changeState(uint8_t state) {
	if(state == 0) {
		programState = 0;
		initMenu();
	}
	else if(state == 1) {
		programState = 1;
		initGame();
	}
	else if(state == 2) {
		programState = 2;
		//initGameOver();
	}
}