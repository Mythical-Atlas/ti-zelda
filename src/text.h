#ifndef TEXT_H
#define TEXT_H

#include <stdint.h>

extern const uint8_t LEFT_JUSTIFIED;
extern const uint8_t CENTER_JUSTIFIED;
extern const uint8_t RIGHT_JUSTIFIED;
extern const uint8_t TOP_ALIGNED;
extern const uint8_t MIDDLE_ALIGNED;
extern const uint8_t BOTTOM_ALIGNED;

extern void initFont();

extern void drawString(char*, uint8_t, uint8_t, int8_t, uint8_t, uint8_t);
extern void drawUInt(uint8_t, uint8_t, uint8_t, int8_t, uint8_t, uint8_t);
extern void drawULong(uint32_t, uint8_t, uint8_t, int8_t, uint8_t, uint8_t);

#endif