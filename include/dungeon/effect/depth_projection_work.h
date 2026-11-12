#ifndef DUNGEON_EFFECT_DEPTH_PROJECTION_WORK_H
#define DUNGEON_EFFECT_DEPTH_PROJECTION_WORK_H

#include "common.h"
#include "sdk/libgte_matrix.h"

/* Stack work of the relative-depth effect updates: RotTransPers projects the effect position, then
 * its anchor, through position and returns each depth; its screen XY, depth cue and flag outputs land
 * in the words after it. */
typedef struct DepthProjectionWork {
    SVECTOR position;
    s32 screen_xy;
    s32 pad_0C;
    s32 depth_cue;
    s32 gte_flag;
} DepthProjectionWork;

#endif
