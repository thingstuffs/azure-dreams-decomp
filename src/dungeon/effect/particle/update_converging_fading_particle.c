#include "sdk/libc.h"
#include "common.h"
#include "dungeon/effect/particle.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

typedef struct S_80165164_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union {
        struct { s8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    u8 pad_34[0xE];
    s16 unk_42;
    s16 unk_44;
    u8 pad_46[0x6];
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_80165164_1;   /* arg0 in update_converging_fading_particle */




/* Update effect motion and color, flagging it near its target or when fully faded. */
void update_converging_fading_particle(S_80165164_1 *effect, ObjectPosition *position) {
    s16 fade_level;
    s32 scaled_red;
    s32 scaled_green;
    s32 target_dx;
    s32 target_dy;
    s32 scaled_blue;

    position->x.v = (s32) (position->x.v
        + effect->unk_4C);
    position->y.v = (s32) (position->y.v
        + effect->unk_50);
    position->z.v = (s32) (position->z.v + effect->unk_54);
    effect->unk_4C = (s32) (effect->unk_4C + effect->unk_58);
    effect->unk_50 = (s32) (effect->unk_50 + effect->unk_5C);
    effect->unk_54 = (s32) (effect->unk_54 + effect->unk_60);
    target_dx = abs(effect->unk_42 - position->x.w.i);
    if (target_dx < 0x10) {
        target_dy = abs(effect->unk_44 - position->y.w.i);
        if (target_dy < 0x10) {
            NODE_HEADER(effect)->flags = (u16) (NODE_HEADER(effect)->flags | NODE_REMOVE);
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
    }
    scaled_red = effect->unk_00 * effect->unk_32;
    effect->unk_04.at00.v = (s8) (scaled_red / 256);
    scaled_green = effect->unk_01 * effect->unk_32;
    effect->unk_04.at01.v = (s8) (scaled_green / 256);
    scaled_blue = effect->unk_02 * effect->unk_32;
    effect->unk_04.at02.v = (s8) (scaled_blue / 256);
    fade_level = (u16) effect->unk_32 - 8;
    effect->unk_32 = fade_level;
    effect->unk_08 = (s32) effect->unk_04.at00u.v;
    if ((fade_level << 0x10) <= 0) {
        NODE_HEADER(effect)->flags = (u16) (NODE_HEADER(effect)->flags | NODE_REMOVE);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
