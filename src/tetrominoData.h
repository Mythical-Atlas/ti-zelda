#ifndef TETROMINO_DATA_H
#define TETROMINO_DATA_H

#include <stdint.h>
#include <stdbool.h>

extern const uint8_t MINO_COLORS[7];

extern const bool ORIENTATIONS[7][4][4][4];

extern const uint8_t WIDTHS[7][4];
extern const uint8_t HEIGHTS[7][4];

extern const int8_t OTHER_TESTS[8][5][2];
extern const int8_t I_TESTS[8][5][2];

#endif