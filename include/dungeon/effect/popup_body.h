#ifndef DUNGEON_EFFECT_POPUP_BODY_H
#define DUNGEON_EFFECT_POPUP_BODY_H

#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"

/* create_actor_value_popup installs either fading callback on this body. */
typedef struct ActorValuePopupBody {
    ObjectNodeHeader *owner;
    /* UNION: src/dungeon/effect/update_anchored_fading_effect.c:56,116,119; src/dungeon/effect/update_attached_fading_effect.c:65,125,128 - the same velocity word is stored and read whole (lw/sw, >> 1) and read through its high halfword. */
    union { struct { s32 v; } at00; struct { u8 pad[2]; s16 v; } at02; } bounce_velocity;
    s16 phase;
    u16 phase_ticks;
    u16 frame_count;
    s16 flashing;
    s16 start_delay;
    u8 pad_12[2];
    ObjectPosition *anchor_position;
    u16 anchor_x;
    u16 anchor_y;
    u16 anchor_z;
} ActorValuePopupBody;

#endif
