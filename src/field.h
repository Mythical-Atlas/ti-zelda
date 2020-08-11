// stuff that involves the playfield

#ifndef FIELD_H
#define FIELD_H

#include <stdint.h>

extern const uint8_t COLOR_FIELD;

extern const uint8_t MINO_EMPTY;
extern const uint8_t MINO_I;
extern const uint8_t MINO_O;
extern const uint8_t MINO_T;
extern const uint8_t MINO_S;
extern const uint8_t MINO_Z;
extern const uint8_t MINO_J;
extern const uint8_t MINO_L;

extern int8_t minos[22][10];

extern void initField();
extern void updateField();
extern void drawField();

extern void moveLinesDown(uint8_t);

#endif