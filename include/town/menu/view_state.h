#ifndef TOWN_MENU_VIEW_STATE_H
#define TOWN_MENU_VIEW_STATE_H

#include "common.h"

/* Camera-derived source state sampled by fading triangle effects. */
typedef struct {
    s16 base_x;
    s16 angle;
    u16 camera_x;
    u16 camera_y;
    s32 intensity_scale;
    s16 spawn_cooldown;
} State;

#endif
