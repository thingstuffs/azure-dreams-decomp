#include "common.h"
#include "shared/object_flags.h"

typedef struct S_8002744C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8002744C_0;   /* arg1 in advance_effect_positions_and_fade */

typedef struct S_8002744C_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x4E];
    s16 unk_66;
} S_8002744C_1;   /* arg0 in advance_effect_positions_and_fade */

typedef struct S_8002744C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_8002744C_2;   /* arg2 in advance_effect_positions_and_fade */


/* Advance effect positions, fade the color, and flag expiration when the timer ends. */
void advance_effect_positions_and_fade(void *effect_arg, void *positions_arg, void *color_arg) {
    S_8002744C_2 *color = color_arg;
    S_8002744C_0 *positions = positions_arg;
    S_8002744C_1 *effect = effect_arg;
    s16 ticks_left;
    u8 intensity;

    positions->unk_00 += effect->unk_0C;
    positions->unk_04 += effect->unk_10;
    positions->unk_08 += effect->unk_14;

    positions->unk_0C += effect->unk_0C >> 1;
    positions->unk_10 += effect->unk_10 >> 1;
    positions->unk_14 += effect->unk_14 >> 1;

    intensity = color->unk_0C;
    intensity -= intensity / effect->unk_66;
    color->unk_0C = intensity;
    color->unk_0D = intensity;
    color->unk_0E = intensity;

    ticks_left = (u16)effect->unk_66 - 1;
    effect->unk_66 = ticks_left;
    if ((ticks_left << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
