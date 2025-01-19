#include "input.h"
#include "defs.h"

void doInput(struct GameState *gameState, struct PlayerStruct *playerStruct) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			gameState->isRunning = false;
		}
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				gameState->isRunning = false;
				break;
			case SDLK_SPACE:
				playerStruct->vel_y = JUMP_FORCE;
				break;

			case SDLK_p:
				gameState->isPaused = !gameState->isPaused;
				// Optional: gameIsPaused ? Mix_PauseMusic() : Mix_ResumeMusic();
				break;
			}
		}
	}
}
