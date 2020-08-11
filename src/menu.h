// the menu states (main, options, controls, game over)

#ifndef MENU_H
#define MENU_H

#include <stdint.h>

extern uint8_t menuState;
extern uint8_t menuTimer;
extern uint8_t menuSelection;

extern void initMenu();
extern void updateMenu();
extern void drawMenu();

#endif