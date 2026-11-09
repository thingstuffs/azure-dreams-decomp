#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "dungeon/effect/sprite.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "slus.h"

typedef struct S_800D81D4_0 {
    u8 pad_00[0xC];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x8];
    u16 unk_18;
    u8 pad_1A[0x2];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_1C;   /* overlapping accesses */
    u8 pad_20[0x8];
    s32 unk_28;
    u8 pad_2C[0x1C];
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
} S_800D81D4_0;   /* arg0 in update_orbiting_effect_particle */

typedef struct S_800D81D4_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    s32 unk_08;
    u8 pad_0C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_800D81D4_1;   /* p1 in update_orbiting_effect_particle */

/* Updates a rotating effect's motion, color, and lifetime. */
void update_orbiting_effect_particle(S_800D81D4_0 *effect, S_800D81D4_1 *motion, void *primitive_data) {
    s32 phase_index;
    s32 height_offset;
    SpriteFrameState *primitive= primitive_data;

    effect->unk_48 = effect->unk_48 - 1;
    advance_sprite_animation_and_textures(primitive);
    phase_index = effect->unk_4C;
    switch (phase_index) {
    default:
        motion->unk_02 = (s16) (effect->unk_0C + ((s32) (rsin((s16) effect->unk_18) * effect->unk_1C.at02.v)
            >> 0xC));
        motion->unk_06 = (s16) (effect->unk_0E + ((s32) (rcos((s16) effect->unk_18) * effect->unk_1C.at02.v)
            >> 0xC));
        return;
    case 0:
        effect->unk_48 = 0x10U;
        height_offset = (rand() % 96) - 0x30;
        motion->unk_14.at00.v = (s32) ((s32) (height_offset << 0x10) / effect->unk_48);
        effect->unk_28 = (s32) ((s32) (SquareRoot0(0x900 - (height_offset * height_offset))
            << 0x10) / effect->unk_48);
        effect->unk_18 = rand();
        effect->unk_4C++;
    case 1:
    {
        s32 motion_value;
        s32 motion_value_2;
        s32 motion_step;
        s32 motion_step_2;
        s32 color_step;

        motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14.at00.v);
        motion_value_2 = effect->unk_1C.at00.v;
        motion_step_2 = effect->unk_28;
        color_step = 0x40000;
        effect->unk_1C.at00.v = motion_value_2 + motion_step_2;
        color_step |= 0x404;
        primitive->color.word = primitive->color.word + color_step;
        motion_step = effect->unk_48;
        motion_value = 0x20 - motion_step;
        motion_step = effect->unk_4A;
        motion_value <<= 3;
        effect->unk_18 = (u16) (effect->unk_18 + (motion_value * motion_step));
        if (effect->unk_48 >= 0) {
            break;
        }
    }
        effect->unk_48 = 0x14U;
        effect->unk_4C++;
        break;
    case 2:
        effect->unk_18 = (u16) (effect->unk_18 + (effect->unk_4A * 0x140));
        if (effect->unk_48 > 0) {
            break;
        }
        effect->unk_48 = 0x1CU;
        effect->unk_4C++;
        break;
    case 3:
        motion->unk_08 = (s32) (motion->unk_08 - ((s32) motion->unk_14.at00.v >> 1));
        effect->unk_1C.at00.v = (s32) (effect->unk_1C.at00.v - ((s32) effect->unk_28 >> 1));
        primitive->color.word = (s32) (primitive->color.word + 0x30303);
        effect->unk_18 = (u16) (effect->unk_18 + ((((0x1C - effect->unk_48) * 8) + 0x140) * effect->unk_4A));
        if (effect->unk_48 > 0) {
            break;
        }
        effect->unk_48 = 0U;
        effect->unk_4C++;
        break;
    case 4:
        effect->unk_18 = (u16) (effect->unk_18 + ((((0 - effect->unk_48) * 0x10) + 0x1E0) * effect->unk_4A));
        primitive->color.word = (s32) (primitive->color.word + 0x40404);
        if ((u8) primitive->color.word < 0xF1U) {
            break;
        }
        primitive->tpage_abr = 0x60;
        motion->unk_14.at02.v = (s16) (0 - (rand() & 3));
        effect->unk_4C++;
        break;
    case 5:
        motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14.at00.v);
        motion->unk_14.at00.v = (s32) (motion->unk_14.at00.v - ((rand() & 0xFFF) << 6));
        effect->unk_1C.at00.v = (s32) (effect->unk_1C.at00.v - 0x8000);
        effect->unk_18 = (u16) (effect->unk_18 + ((((0 - effect->unk_48) * 0x10) + 0x1E0) * effect->unk_4A));
        primitive->color.word = (s32) (primitive->color.word + 0xFFE7E7E8);
        if ((u8) primitive->color.word >= 0x18U) {
            break;
        }
        effect->unk_4C++;
        break;
    case 6:
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        (*&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
    motion->unk_02 = (s16) (effect->unk_0C + ((s32) (rsin((s16) effect->unk_18) * effect->unk_1C.at02.v)
        >> 0xC));
    motion->unk_06 = (s16) (effect->unk_0E + ((s32) (rcos((s16) effect->unk_18) * effect->unk_1C.at02.v)
        >> 0xC));
    return;
}
