#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdint.h>
#include <stdbool.h>

// constants

extern const uint8_t MOVE_DELAY;
extern const uint8_t MOVE_SPEED;

extern const uint8_t DROP_DELAY;
extern const uint8_t DROP_SPEED;
extern const uint8_t PLACE_DELAY;
extern const uint8_t GRAVITY_START;
extern const uint8_t GRAVITY_INTERVAL;

// variables

extern uint8_t moveDelayTimer;
extern uint8_t moveTimer;
extern int8_t moveDir;
extern uint8_t moveState;

extern bool placing;

extern uint8_t tetrominoType;
extern int8_t tetrominoX;
extern int8_t tetrominoY;
extern uint8_t tetrominoW;
extern uint8_t tetrominoH;
extern uint8_t tetrominoOrientation;

extern int8_t oldX;
extern int8_t oldY;
extern uint8_t oldOrientation;

extern uint8_t gravityTimer;
extern uint8_t gravitySpeed;
extern uint8_t dropDelayTimer;
extern uint8_t dropTimer;
extern uint8_t dropState;
extern uint8_t placeTimer;

// functions

extern void initTetromino();
extern void updateTetromino();
extern void drawTetromino();

extern void checkPlacing();
extern void placeTetromino();
extern void generateTetromino();
extern void getTetrominoSize();
extern bool checkCollision();
extern void wallKick();

#endif