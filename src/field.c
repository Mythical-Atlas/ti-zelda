#include "field.h"

/*#include <tice.h>*/
#include <graphx.h>
/*#include <keypadc.h>
#include <debug.h>
#include <fileioc.h>
#include <fontlibc.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>*/
#include <stdbool.h>

#include <math.h>
/*#include <string.h>
#include <ctype.h>*/

#include "tetromino.h"
#include "tetrominoData.h"
#include "game.h"
#include "main.h"

const uint8_t COLOR_FIELD = 0x01;

const uint8_t MINO_EMPTY = -1;
const uint8_t MINO_I = 0;
const uint8_t MINO_O = 1;
const uint8_t MINO_T = 2;
const uint8_t MINO_S = 3;
const uint8_t MINO_Z = 4;
const uint8_t MINO_J = 5;
const uint8_t MINO_L = 6;

int8_t minos[22][10];

void initField() {
	uint8_t ix;
	uint8_t iy;
	
	for(ix = 0; ix < 10; ix++) {for(iy = 0; iy < 22; iy++) {minos[iy][ix] = MINO_EMPTY;}}
}
void updateField() {
	uint8_t ix;
	uint8_t iy;
	uint8_t i;
	bool success;
	
	for(iy = 0; iy < 22; iy++) {
		success = true;
		
		for(ix = 0; ix < 10; ix++) {
			if(minos[iy][ix] == -1) {
				success = false;
				break;
			}
		}
		
		if(success) {
			for(ix = 0; ix < 10; ix++) {minos[iy][ix] = -1;}
			
			moveLinesDown(iy - 1);
			
			linesCleared++;
			level = (uint8_t)floor(linesCleared / 10) + 1;
			if(level > 20) {level = 20;}
			
			gravitySpeed = GRAVITY_START;
			for(i = 0; i < level; i++) {
				if(gravitySpeed > GRAVITY_INTERVAL) {gravitySpeed -= GRAVITY_INTERVAL;}
				else {gravitySpeed = 0;}
			}
		}
	}
}
void drawField() {
	uint8_t ix;
	uint8_t iy;
	
	gfx_SetColor(COLOR_FIELD);
	gfx_FillRectangle(BORDER_WIDTH, 0, FIELD_WIDTH * TILE_WIDTH, FIELD_HEIGHT * TILE_HEIGHT);
	
	for(ix = 0; ix < 10; ix++) {
		for(iy = 0; iy < 22; iy++) {
			if(minos[iy][ix] != -1) {
				gfx_SetColor(MINO_COLORS[minos[iy][ix]]);
				gfx_FillRectangle(BORDER_WIDTH + (ix) * TILE_WIDTH, (iy - 2) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
			}
		}
	} 
}

void moveLinesDown(uint8_t bottom) {
	uint8_t ix;
	uint8_t iy;
	
	for(iy = bottom; iy > 0; iy--) {for(ix = 0; ix < 10; ix++) {minos[iy + 1][ix] = minos[iy][ix];}}
}