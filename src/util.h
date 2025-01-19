#ifndef UTIL_H
#define UTIL_H

#include "structs.h"

void setPipeOffScreen(struct PipeStruct *pipe, int x_offset);
void capFrameRate(Uint64 *frameStart, Uint64 *lastTime, double *deltaTime, int *frameTime);

#endif
