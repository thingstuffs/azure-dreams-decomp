#ifndef SLUS_STATE_DEFAULTS_H
#define SLUS_STATE_DEFAULTS_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"

#include "common.h"

extern void bzero(void *dst, s32 len);
extern void bind_view_triplet_source(void *entity);

extern s32 camera_default_rotation_xy;
extern s32 camera_default_rotation_tail;
extern s32 camera_default_origin_xy;
extern s32 camera_default_origin_tail;

/* Initialize state fields from globals and clear associated state. */

void reset_camera_transition_fields(void);

#endif
