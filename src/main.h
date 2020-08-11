#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdbool.h>

extern const uint16_t CLOCK_SPEED;
extern const uint16_t KHZ;
extern const uint8_t FPS;

extern const uint8_t COLOR_BG;
extern const uint8_t COLOR_FONT;

extern uint8_t programState;
extern bool running;
extern uint32_t realFPS;

extern bool keyUp;
extern bool keyDown;
extern bool keyLeft;
extern bool keyRight;
extern bool key2nd;
extern bool keyMode;
extern bool keyDel;
extern bool keyEnter;
extern bool keyClear;

extern bool keyUpReady;
extern bool keyDownReady;
extern bool keyLeftReady;
extern bool keyRightReady;
extern bool key2ndReady;
extern bool keyModeReady;
extern bool keyDelReady;
extern bool keyEnterReady;
extern bool keyClearReady;

extern void changeState(uint8_t);

#endif