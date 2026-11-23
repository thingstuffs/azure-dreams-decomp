#ifndef DUNGEON_OVL_BC9094_H
#define DUNGEON_OVL_BC9094_H
#include "engine/node/registration.h"

#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/status.h"

typedef struct Object {
    ObjectNodeHeader header;
    ActorRecord body_20;
} Object;

extern u8 nyuel_slot_d_action_callback[9];
extern u8 nyuel_frame_set_7[9];
extern u8 D_80162F00[9];
extern u8 D_8015EA98[9];

extern void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
extern s32 generate_random_value(void);

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */

void *spawn_nyuel(s16 spawn_flags, s16 tile_x, s32 tile_y, s32 spawn_height);
#endif
