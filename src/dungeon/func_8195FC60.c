#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/object_flags.h"






/* Advance motion, fade the effect, and flag expiry when its timer runs out. */
void func_80025460(u16 *state, Motion *motion, Effect *effect)
{
    u8 brightness;
    s16 ticks_left;

    (*(u16 *)&D_80027330)++;

    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;
    motion->dz += 0x40000;

    effect->x += effect->dx;
    effect->y += effect->dy;

    brightness = effect->red;
    brightness = brightness - brightness / *(s16 *)((u8 *)state + 0x4C);
    effect->blue = effect->green = effect->red = brightness;

    ticks_left = state[0x26] - 1;
    state[0x26] = ticks_left;
    if ((ticks_left << 16) <= 0) {
        state[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
