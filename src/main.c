#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define GRAVITY 9.81

struct playerStruct {
  SDL_Surface *playerSurface;
  SDL_Texture *playerTexture;
  SDL_Rect positionRect;
  float vel_y;
};

void freePlayerResources(struct playerStruct *player) {
  SDL_FreeSurface(player->playerSurface);
  SDL_DestroyTexture(player->playerTexture);
}

int initPlayerStruct(struct playerStruct *player, SDL_Renderer *renderer) {
  // Initialize the surface for the player character
  player->playerSurface = IMG_Load("./images/pretzel.png");
  if (player->playerSurface == NULL) {
    printf("Awww shit, here we go again: %s\n", IMG_GetError());
    return -1;
  }

  // Use that surface to create the player texture
  player->playerTexture =
      SDL_CreateTextureFromSurface(renderer, player->playerSurface);

  if (player->playerSurface == NULL) {
    printf("Aww shite, here we go again: %s\n", SDL_GetError());
    return -1;
  }

  player->positionRect.x = SCREEN_WIDTH / 3 - 50;
  player->positionRect.y = SCREEN_HEIGHT / 2 - 50;
  player->positionRect.w = 128;
  player->positionRect.h = 128;

  player->vel_y = 0.0f;

  return 0;
}

int main(int argc, char *args[]) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  struct playerStruct player = {0};

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("could not initialize sdl2: %s\n", SDL_GetError());
    return -1;
  }
  window = SDL_CreateWindow("Flappy Pretzel", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("could not create window: %s\n", SDL_GetError());
    return -1;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    printf("Could not create renderer: %s\n", SDL_GetError());
    return -1;
  }

  if (initPlayerStruct(&player, renderer) < 0) {
    printf("Error initializing player struct\n");
    return -1;
  }

  // Main game loop
  SDL_Event event;
  bool gameIsRunning = true;
  while (gameIsRunning) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, player.playerTexture, NULL, &player.positionRect);
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        gameIsRunning = false;
      }
    }
    SDL_RenderPresent(renderer);
  }

  freePlayerResources(&player);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
