#include "tetromino.h"

/*#include <tice.h>*/
#include <graphx.h>
/*#include <keypadc.h>
#include <debug.h>
#include <fileioc.h>
#include <fontlibc.h>*/

#include <stdio.h>
/*#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <math.h>
#include <string.h>
#include <ctype.h>*/

#include "main.h"
#include "game.h"
#include "field.h"
#include "tetrominoData.h"

const uint8_t MOVE_DELAY = 5;
const uint8_t MOVE_SPEED = 1;

const uint8_t DROP_DELAY = 5;
const uint8_t DROP_SPEED = 1;
const uint8_t PLACE_DELAY = 5;
const uint8_t GRAVITY_START = 20;
const uint8_t GRAVITY_INTERVAL = 2;

uint8_t moveDelayTimer;
uint8_t moveTimer;
int8_t moveDir;
uint8_t moveState;

bool placing;

uint8_t tetrominoType;
int8_t tetrominoX;
int8_t tetrominoY;
uint8_t tetrominoW;
uint8_t tetrominoH;
uint8_t tetrominoOrientation;

int8_t oldX;
int8_t oldY;
uint8_t oldOrientation;

uint8_t gravityTimer;
uint8_t gravitySpeed;
uint8_t dropDelayTimer;
uint8_t dropTimer;
uint8_t dropState;
uint8_t placeTimer;

void initTetromino() {
	moveDelayTimer = 0;
	moveTimer = 0;
	moveDir = 0;
	moveState = 0;

	placing = 0;

	tetrominoOrientation = 0;

	dropDelayTimer = 0;
	dropTimer = 0;
	dropState = 0;
	placeTimer = 0;
}

void updateTetromino() {
	// move state + direction handling
	
	if(keyLeft && keyLeftReady || keyLeft && !keyRight || keyLeft && moveDir == -1) {
		keyLeftReady = 0;
		
		if(moveDir != -1) {
			moveState = 0;
			moveDir = -1;
		}
	}
	
	if(keyRight && keyRightReady || keyRight && !keyLeft || keyRight && moveDir == 1) {
		keyRightReady = 0;
		
		if(moveDir != 1) {
			moveState = 0;
			moveDir = 1;
		}
	}
	
	// stop moving if no buttons pressed
	if(!keyLeft && !keyRight) {
		moveState = 0;
		moveDir = 0;
	}
	
	// movement
	
	if(moveState == 0) { // initial move
		oldX = tetrominoX;
		oldY = tetrominoY;
		tetrominoX += moveDir;
		wallKick();
		
		moveState = 1;
		moveDelayTimer = 0;
		
		if(moveDir != 0 && oldX != tetrominoX) {placeTimer = 0;}
	}
	else if(moveState == 1) { // wait for continuous movement
		moveDelayTimer++;
		if(moveDelayTimer >= MOVE_DELAY) {
			oldX = tetrominoX;
			oldY = tetrominoY;
			tetrominoX += moveDir;
			wallKick();
			
			moveState = 2;
			moveTimer = 0;
			
			if(oldX != tetrominoX) {placeTimer = 0;}
		}
	}
	else if(moveState == 2) { // continuous movement
		moveTimer++;
		if(moveTimer >= MOVE_SPEED) {
			oldX = tetrominoX;
			oldY = tetrominoY;
			tetrominoX += moveDir;
			wallKick();
			
			moveTimer = 0;
			
			if(oldX != tetrominoX) {placeTimer = 0;}
		}
	}
	
	// fast drop state handling
	
	if(keyDown && keyDownReady && dropState == 0) {
		keyDownReady = 0;
		dropState = 1;
	}
	if(keyDown && keyDownReady && placing) {
		keyDownReady = 0;
		placing = 0;
		
		placeTetromino();
		generateTetromino();
	}
	
	// stop fast dropping if no buttons pressed
	if(!keyDown && dropState != 0) {
		dropState = 0;
		gravityTimer = 0;
	}
	
	// rotation
	
	if(key2nd && key2ndReady) {
		key2ndReady = 0;
		
		oldOrientation = tetrominoOrientation;
		
		tetrominoOrientation--;
		if(tetrominoOrientation > 3) {tetrominoOrientation = 3;}
		
		getTetrominoSize();
		wallKick();
		
		// delay placement if rotation was successful
		if(oldOrientation != tetrominoOrientation) {
			placeTimer = 0;
			oldOrientation = tetrominoOrientation;
		}
	}
	if(keyMode && keyModeReady) {
		keyModeReady = 0;
		
		oldOrientation = tetrominoOrientation;
		
		tetrominoOrientation++;
		if(tetrominoOrientation > 3) {tetrominoOrientation = 0;}
		
		getTetrominoSize();
		wallKick();
		
		// delay placement if rotation was successful
		if(oldOrientation != tetrominoOrientation) {
			placeTimer = 0;
			oldOrientation = tetrominoOrientation;
		}
	}
	
	// drop
	
	if(!placing) {
		if(dropState == 0) { // regular gravity
			if(gravityTimer >= gravitySpeed) {
				tetrominoY++;
				
				gravityTimer = 0;
			}
			gravityTimer++;
		}
		else if(dropState == 1) { // initial drop
			tetrominoY++;
			
			dropState  = 2;
			dropDelayTimer = 0;
		}
		else if(dropState == 2) { // wait for fast drop
			dropDelayTimer++;
			if(dropDelayTimer >= DROP_DELAY) {
				tetrominoY++;
				
				dropState = 3;
				dropTimer = 0;
			}
		}
		else if(dropState == 3) { // fast drop
			tetrominoY++;
		}
	}
	
	// place
	
	if(keyUp && keyUpReady) {
		keyUpReady = 0;
		
		while(!checkCollision()) {tetrominoY++;}
		tetrominoY--;
		
		placing = 0;
		placeTetromino();
		generateTetromino();
	}
	else {
		checkPlacing();
		if(placing) {
			if(keyDown && placeTimer >= PLACE_DELAY - 1 || !keyDown && placeTimer >= gravitySpeed - 1) {
				placing = 0;
				placeTetromino();
				generateTetromino();
			}
			placeTimer++;
		}
	}
}
void drawTetromino() {
	uint8_t ix, iy;
	
	gfx_SetColor(MINO_COLORS[tetrominoType]);
	for(ix = 0; ix < 4; ix++) {for(iy = 0; iy < 4; iy++) {if(ORIENTATIONS[tetrominoType][tetrominoOrientation][iy][ix]) {gfx_FillRectangle(BORDER_WIDTH + (tetrominoX + ix) * TILE_WIDTH, (tetrominoY + iy) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);}}}
}

void checkPlacing() {
	int8_t oy = tetrominoY;
	
	tetrominoY++;
	
	if(checkCollision()) {
		tetrominoY = oy;
		if(!placing) {placeTimer = 0;}
		placing = 1;
	}
	else {
		tetrominoY = oy;
		placing = 0;
	}
}
void placeTetromino() {
	uint8_t ix;
	uint8_t iy;
	uint8_t x;
	uint8_t y;
	
	saved = 0;
	
	for(ix = 0; ix < 4; ix++) {
		for(iy = 0; iy < 4; iy++) {
			x = tetrominoX + ix;
			y = tetrominoY + 2 + iy;
			
			if(ORIENTATIONS[tetrominoType][tetrominoOrientation][iy][ix]) {minos[y][x] = tetrominoType;}
		}
	}
}
void generateTetromino() {
	tetrominoType = nextTetromino;
	
	srand(rtc_Time());
	nextTetromino = random();
	while(nextTetromino > 6) {nextTetromino = random();}
	
	tetrominoX = 3;
	tetrominoY = -1;
	tetrominoOrientation = 0;
	
	oldX = tetrominoX;
	oldY = tetrominoY;
	oldOrientation = tetrominoOrientation;
	
	getTetrominoSize();
	
	gravityTimer = 0;
	
	if(checkCollision()) {changeState(2);}
}
void getTetrominoSize() {
	tetrominoW = WIDTHS[tetrominoType][tetrominoOrientation];
	tetrominoH = HEIGHTS[tetrominoType][tetrominoOrientation];
}
bool checkCollision() {
	uint8_t ix;
	uint8_t iy;
	uint8_t x;
	uint8_t y;
	
	for(ix = 0; ix < 4; ix++) {
		for(iy = 0; iy < 4; iy++) {
			x = tetrominoX + ix;
			y = tetrominoY + 2 + iy;
			
			if(ORIENTATIONS[tetrominoType][tetrominoOrientation][iy][ix] && (minos[y][x] != -1 || x < 0 || x >= FIELD_WIDTH || y >= FIELD_HEIGHT + 2)) {return(1);}
		}
	}
	
	return(0);
}
void wallKick() {
	int8_t ox = tetrominoX;
	int8_t oy = tetrominoY;
	uint8_t tx = 0;
	uint8_t ty;
	
	bool success = false;
	
	if(oldOrientation == tetrominoOrientation) {
		if(checkCollision()) {
			tetrominoX = oldX;
			tetrominoY = oldY;
		}
	}
	else {
		     if(oldOrientation == 0 && tetrominoOrientation == 1) {tx = 0;}
		else if(oldOrientation == 1 && tetrominoOrientation == 0) {tx = 1;}
		else if(oldOrientation == 1 && tetrominoOrientation == 2) {tx = 2;}
		else if(oldOrientation == 2 && tetrominoOrientation == 1) {tx = 3;}
		else if(oldOrientation == 2 && tetrominoOrientation == 3) {tx = 4;}
		else if(oldOrientation == 3 && tetrominoOrientation == 2) {tx = 5;}
		else if(oldOrientation == 3 && tetrominoOrientation == 0) {tx = 6;}
		else if(oldOrientation == 0 && tetrominoOrientation == 3) {tx = 7;}
		
		for(ty = 0; ty < 5; ty++) {
			if(tetrominoType != MINO_I) {
				tetrominoX = ox + OTHER_TESTS[tx][ty][0];
				tetrominoY = oy - OTHER_TESTS[tx][ty][1];
				if(!checkCollision()) {
					success = true;
					break;
				}
			}
			else {
				tetrominoX = ox + I_TESTS[tx][ty][0];
				tetrominoY = oy - I_TESTS[tx][ty][1];
				if(!checkCollision()) {
					success = true;
					break;
				}
			}
		}
		
		if(!success) {
			tetrominoX = ox;
			tetrominoY = oy;
			tetrominoOrientation = oldOrientation;
		}
	}
}