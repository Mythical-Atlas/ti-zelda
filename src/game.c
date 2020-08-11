#include "game.h"

/*#include <tice.h>*/
#include <graphx.h>
/*#include <keypadc.h>*/
#include <debug.h>
/*#include <fileioc.h>
#include <fontlibc.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <math.h>
#include <string.h>
#include <ctype.h>*/

#include "main.h"
#include "field.h"
#include "tetromino.h"
#include "tetrominoData.h"
#include "text.h"

const uint8_t BORDER_WIDTH = 100;
const uint8_t FIELD_WIDTH = 10; // in tiles
const uint8_t FIELD_HEIGHT = 20; // in tiles
const uint8_t TILE_WIDTH = 12;
const uint8_t TILE_HEIGHT = 12;

const uint8_t COLOR_GHOST = 0x02;

uint8_t linesCleared;
uint8_t level;
uint8_t nextTetromino;
int8_t savedTetromino;
bool saved;
int8_t ghostY;

void initGame() {
	uint8_t ix;
	uint8_t iy;
	
	initField();
	
	// generate next tetromino
	srand(rtc_Time());
	nextTetromino = random();
	while(nextTetromino > 6) {nextTetromino = random();}
	
	// make a new tetromino for the start of the game
	generateTetromino();
	
	linesCleared = 0;
	level = 1;
	gravitySpeed = GRAVITY_START;
	gravityTimer = 0;
	savedTetromino = -1;
	saved = 0;
}
void updateGame() {
	int8_t oy;
	
	int8_t ts = savedTetromino;
	int8_t tt = tetrominoType;
	
	if(keyClear && keyClearReady) {
		keyClearReady = 0;
		changeState(2);
	}
	else {
		if(!saved && keyDel && keyDelReady) {
			keyDelReady = 0;
			
			if(savedTetromino != -1) {
				tetrominoType = ts;
				savedTetromino = tt;
			}
			else {
				savedTetromino = tetrominoType;
				generateTetromino();
			}
			
			saved = 1;
		}
		else {updateTetromino();}
		
		updateField();
		
		oy = tetrominoY;
		while(!checkCollision()) {tetrominoY++;}
		ghostY = tetrominoY - 1;
		tetrominoY = oy;
		
		dbg_ClearConsole();
		
		dbg_sprintf(dbgout, "tetromino type = %u\n", tetrominoType);
		dbg_sprintf(dbgout, "tetromino orientation = %u\n", tetrominoOrientation);
		dbg_sprintf(dbgout, "tetromino x = %i\n", tetrominoX);
		dbg_sprintf(dbgout, "tetromino y = %i\n", tetrominoY);
		dbg_sprintf(dbgout, "tetromino w = %u\n", tetrominoW);
		dbg_sprintf(dbgout, "tetromino h = %u\n\n", tetrominoH);
	}
}
void drawGame() {
	uint8_t ix;
	uint8_t iy;
	
	gfx_FillScreen(COLOR_BG);
	
	drawField();
	
	gfx_SetColor(COLOR_GHOST);
	for(ix = 0; ix < 4; ix++) {for(iy = 0; iy < 4; iy++) {if(ORIENTATIONS[tetrominoType][tetrominoOrientation][iy][ix]) {gfx_Rectangle(BORDER_WIDTH + (tetrominoX + ix) * TILE_WIDTH, (ghostY + iy) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);}}}
	
	drawTetromino();
	
	drawString("Lines cleared:", 0, 0, 0, LEFT_JUSTIFIED, TOP_ALIGNED);
	drawUInt(linesCleared, 0, 0, 1, LEFT_JUSTIFIED, TOP_ALIGNED);
	
	drawString("Level:", 0, 0, 3, LEFT_JUSTIFIED, TOP_ALIGNED);
	drawUInt(level, 0, 0, 4, LEFT_JUSTIFIED, TOP_ALIGNED);
	
	drawString("Next:", 320 - 4 * TILE_WIDTH, 0, 0, RIGHT_JUSTIFIED, TOP_ALIGNED);
	drawString("Saved:", 320 - 4 * TILE_WIDTH, 240, 0, RIGHT_JUSTIFIED, BOTTOM_ALIGNED);
	
	gfx_SetColor(MINO_COLORS[nextTetromino]);
	for(ix = 0; ix < 4; ix++) {for(iy = 0; iy < 4; iy++) {if(ORIENTATIONS[nextTetromino][0][iy][ix]) {gfx_FillRectangle(320 - 4 * TILE_WIDTH + ix * TILE_WIDTH, iy * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);}}}
	
	if(savedTetromino != -1) {
		gfx_SetColor(MINO_COLORS[savedTetromino]);
		for(ix = 0; ix < 4; ix++) {for(iy = 0; iy < 4; iy++) {if(ORIENTATIONS[savedTetromino][0][iy][ix]) {gfx_FillRectangle(320 - 4 * TILE_WIDTH + ix * TILE_WIDTH, 240 - 4 * TILE_WIDTH + iy * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);}}}
	}
	
	drawString("FPS", 0, 240, -1, LEFT_JUSTIFIED, BOTTOM_ALIGNED);
	drawULong(realFPS, 0, 240, 0, LEFT_JUSTIFIED, BOTTOM_ALIGNED);
	
	gfx_Blit(gfx_buffer);
}