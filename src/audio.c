#include "audio.h"

int initAudioAssets(struct GameAssets *gameAssets) {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	gameAssets->audioAssets.backgroundMusic = Mix_LoadMUS("../assets/sound/main-music.mp3");
	if (gameAssets->audioAssets.backgroundMusic == NULL) {
		printf("Failed to load background music: %s\n", Mix_GetError());
		return -1;
	}

	gameAssets->audioAssets.pretzelSFX1 = Mix_LoadWAV("../assets/sound/pretzel1.mp3");
	if (gameAssets->audioAssets.pretzelSFX1 == NULL) {
		printf("Failed to load pretzelSFX1: %s\n", Mix_GetError());
		return -1;
	}

	if (Mix_VolumeMusic(BACKGROUND_VOLUME_LEVEL) < 0) {
		printf("Failed to reduce music: %s\n", Mix_GetError());
		return -1;
	}

	if (Mix_PlayMusic(gameAssets->audioAssets.backgroundMusic, -1) < 0) {
		printf("Failed to start playing background music: %s\n", Mix_GetError());
		return -1;
	}

	return 0;
}
