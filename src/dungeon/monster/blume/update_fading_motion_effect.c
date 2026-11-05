#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/blume.h"

typedef struct S_80171284_0 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u8 unk_04;
    u8 pad_05[0x1F];
    u16 unk_24;
    u8 pad_26[0x4];
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x20];
    u16 unk_4E;
    u16 unk_50;
} S_80171284_0;   /* arg0 in update_fading_motion_effect */


/* Update the effect countdown and motion, fade its color, and flag expiration. */
void update_fading_motion_effect(void *effect_arg, void *transform_arg, void *color_arg) {
    SpriteFrameState *color = color_arg;
    ObjectPosition *transform = transform_arg;
    S_80171284_0 *effect = effect_arg;
    u16 next_value;
    u16 next_total;
    s16 ticks_left;

    next_value = effect->unk_24 - 1;
    effect->unk_24 = next_value;
    if ((s16)next_value < 8) {
        effect->unk_4E = effect->unk_4E - 1;
    }

    if ((s16)effect->unk_4E < 2) {
        effect->unk_4E = 2;
    }

    if ((s16)effect->unk_24 < 10) {
        next_value = effect->unk_2A + 1;
        next_total = effect->unk_50 + next_value;
        effect->unk_2A = next_value;
        effect->unk_50 = next_total;
    } else {
        effect->unk_50 = effect->unk_50 + 1;
    }

    if ((s16)effect->unk_24 < 11) {
        next_value = effect->unk_2C + 2;
        effect->unk_2C = next_value;
        transform->z.unsigned_parts.integer = transform->z.unsigned_parts.integer - next_value;
    }

    ticks_left = ((s16)effect->unk_24);
    if (ticks_left < 5) {
        color->color.c.r = (effect->unk_02 * ticks_left) / 5;
        color->color.c.g = (effect->unk_03 * ((s16)effect->unk_24)) / 5;
        color->color.c.b = (effect->unk_04 * ((s16)effect->unk_24)) / 5;
    }

    if (((s16)effect->unk_24) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
