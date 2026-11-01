#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/baloon.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;


/* Advance and damp motion, fade the primitive, and flag the effect when its timer expires. */
void advance_damped_fading_effect(DirectionalRandomVelocityEffectBody *effect, Motion *motion, void *primitive) {
    s32 intensity;
    s16 ticks_left;

    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dx /= 2;
    motion->dy /= 2;
    motion->dz /= 2;

    intensity = (effect->unk_0C << 7) /
               effect->unk_0E;
    *(s8 *)((u8 *)primitive + 0xE) = intensity;
    *(s8 *)((u8 *)primitive + 0xD) = intensity;
    *(s8 *)((u8 *)primitive + 0xC) = intensity;

    ticks_left = *(u16 *)((u8 *)effect + 0xC) - 1;
    effect->unk_0C = ticks_left;
    if ((ticks_left << 16) <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
