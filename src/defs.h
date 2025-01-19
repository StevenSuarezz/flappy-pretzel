#ifndef DEFS_H
#define DEFS_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FPS 60
#define GRAVITY 9.81f

const int FRAME_DELAY = 1000 / FPS;
const float JUMP_FORCE = -7.0f;
const float FALL_MULTIPLIER = 1.75f;
const float PLAYER_ANGLE_MULTIPLIER = 3.5f;
const int PIPE_SPEED = 3;
const int PIPE_WIDTH = 100;

const int BACKGROUND_VOLUME_LEVEL = 10;

#endif
