struct PlayerStruct {
	SDL_Texture *playerTexture;
	SDL_Rect positionRect;
	float vel_y;
	int test;
};

struct PipeStruct {
	SDL_Texture *pipeTexture;
	SDL_Rect topPositionRect;
	SDL_Rect bottomPositionRect;
	int gap;
};

struct AudioAssets {
};
