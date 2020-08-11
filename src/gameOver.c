#include "gameOver.h"

#include <graphx.h>

#include "main.h"
#include "text.h"
#include "game.h"

void updateGameOver() {
	if(keyEnter && keyEnterReady) {
		keyEnterReady = 0;
		
		changeState(0);
	}
}
void drawGameOver() {
	// draw background
	gfx_FillScreen(COLOR_BG);
	
	drawString("GAME OVER", 160, 120, -1, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
	drawString("Lines cleared:", 160, 120, 1, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
	drawUInt(linesCleared, 160, 120, 2, CENTER_JUSTIFIED, MIDDLE_ALIGNED);
	drawString("Press enter to continue", 160, 240, 0, CENTER_JUSTIFIED, BOTTOM_ALIGNED);
	
	// swap buffer
	gfx_Blit(gfx_buffer);
}