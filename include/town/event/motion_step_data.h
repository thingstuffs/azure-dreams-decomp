#ifndef TOWN_EVENT_MOTION_STEP_DATA_H
#define TOWN_EVENT_MOTION_STEP_DATA_H

#include "common.h"

/* Signed steps: motion clamps each axis at both -0x100 and +0x100. */
extern s16 town_motion_x_step;
extern s16 town_motion_y_step;

#endif
