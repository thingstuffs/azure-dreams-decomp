#ifndef DUNGEON_MONSTER_GLACIER_ADVANCE_ITEM_MOTION_COLLISION_H
#define DUNGEON_MONSTER_GLACIER_ADVANCE_ITEM_MOTION_COLLISION_H

#include "common.h"
#include "shared/sprite_frame_state.h"

struct ObjectPosition;

typedef struct DirectionalEffectBody {
    u8 pad_00[0x1E];
    union { u16 unsigned_value; s16 signed_value; } remaining_ticks;
    u8 pad_20[0x30];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    s32 acceleration_x;
    s32 acceleration_y;
    s32 acceleration_z;
} DirectionalEffectBody;

void advance_item_motion_collision(DirectionalEffectBody *motion, struct ObjectPosition *position, SpriteFrameState *update);

#endif
