#include "util.h"

void setPipeOffScreen(struct PipeStruct *pipe, int x_offset) {
	// Create a gap of at least 100px and add a random amount to it clamped to
	// 64px
	pipe->gap = (rand() % 64) + 100;

	// Recall that SCREEN_HEIGHT = 480
	int top_min = -440;
	int top_max = -164;
	int top_y = rand() % (top_max - top_min + 1) + top_min;

	int bot_y = top_y + SCREEN_HEIGHT + pipe->gap;

	pipe->topPositionRect.x = SCREEN_WIDTH + x_offset;
	pipe->topPositionRect.y = top_y;
	pipe->topPositionRect.w = PIPE_WIDTH;
	pipe->topPositionRect.h = SCREEN_HEIGHT;

	pipe->bottomPositionRect.x = pipe->topPositionRect.x;
	pipe->bottomPositionRect.y = bot_y;
	pipe->bottomPositionRect.w = PIPE_WIDTH;
	pipe->bottomPositionRect.h = SCREEN_HEIGHT;
}
