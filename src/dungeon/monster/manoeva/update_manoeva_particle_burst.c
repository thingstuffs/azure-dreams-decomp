#include "common.h"
#include "dungeon/monster/manoeva.h"
#include "shared/object_flags.h"


/*
 * Decrements the signed lifetime and flags removal when it expires; otherwise fades RGB toward
 * zero using the remaining ticks, integrates motion, and adds Z acceleration 0x60000.
 */
void update_manoeva_particle_burst(ManoevaParticleBurstBody *effect, s32 *motion, SpriteFrameState *color_data)
{
    u16 ticks_left;
    u8 intensity;

    ticks_left = effect->lifetime.u - 1;
    effect->lifetime.u = ticks_left;
    if ((s16)ticks_left <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    intensity = color_data->color.c.r;
    intensity -= intensity / (s16)ticks_left;
    color_data->color.c.r = intensity;
    color_data->color.c.g = intensity;
    color_data->color.c.b = intensity;

    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
    motion[5] += 0x60000;
}
