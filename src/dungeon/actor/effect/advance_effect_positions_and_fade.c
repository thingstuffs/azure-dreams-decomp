#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/actor/effect.h"


typedef struct S_8002744C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x4E];
    s16 unk_66;
} S_8002744C_1;   /* arg0 in advance_effect_positions_and_fade */


/* Advance effect positions, fade the color, and flag expiration when the timer ends. */
void advance_effect_positions_and_fade(void *effect_arg, void *positions_arg, SpriteFrameState *color_arg) {
    SpriteFrameState *color = color_arg;
    ObjectPosition *positions = positions_arg;
    S_8002744C_1 *effect = effect_arg;
    s16 ticks_left;
    u8 intensity;

    positions->x.v += effect->unk_0C;
    positions->y.v += effect->unk_10;
    positions->z.v += effect->unk_14;

    positions->velocity_x += effect->unk_0C >> 1;
    positions->velocity_y += effect->unk_10 >> 1;
    positions->velocity_z += effect->unk_14 >> 1;

    intensity = color->color.c.r;
    intensity -= intensity / effect->unk_66;
    color->color.c.r = intensity;
    color->color.c.g = intensity;
    color->color.c.b = intensity;

    ticks_left = (u16)effect->unk_66 - 1;
    effect->unk_66 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
