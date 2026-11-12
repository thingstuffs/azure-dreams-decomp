#ifndef TOWN_SCENE_STATE_DATA_H
#define TOWN_SCENE_STATE_DATA_H

#include "common.h"

/* Current scene update state at 0x80019BB0. */
extern s32 scene_update_state;

/* Four-byte context passed to town scene entry dispatchers. */
extern s32 scene_state_dispatch_context;

#endif
