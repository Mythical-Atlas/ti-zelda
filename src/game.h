// global values for the game

#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <stdbool.h>

extern const uint8_t BORDER_WIDTH;
extern const uint8_t FIELD_WIDTH;
extern const uint8_t FIELD_HEIGHT;
extern const uint8_t TILE_WIDTH;
extern const uint8_t TILE_HEIGHT;

extern const uint8_t COLOR_GHOST;

extern uint8_t linesCleared;
extern uint8_t level;
extern uint8_t nextTetromino;
extern int8_t savedTetromino;
extern bool saved;
extern int8_t ghostY;

extern void initGame();
extern void updateGame();
extern void drawGame();

#endif