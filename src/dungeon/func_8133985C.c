#include "common.h"

typedef struct S_8017085C_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    u16 unk_18;
    u8 pad_1A[0x3E];
    s8 unk_58;
    s8 unk_59;
    u8 pad_5A[0x2];
    s32 unk_5C;
} S_8017085C_0;   /* arg0 in func_8017085C */

typedef struct S_8017085C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8017085C_1;   /* arg1 in func_8017085C */

typedef struct S_8017085C_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8017085C_2;   /* arg2 in func_8017085C */



extern s32 func_800644B8();
extern void func_800A7A7C();
extern s32 D_800814A0;

/* Updates vertical animation and triggers an effect upon reaching the resting height. */
void func_8017085C(void *motion, void *position, void *effect) {
    s8 effect_args[4];
    s16 world_z;
    s16 state;
    s16 world_x;
    s32 phase;
    s32 tile_z;
    s32 height_offset;
    s32 centered_z;
    register u16 frame ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u16 elapsed;
    u16 old_state;

    state = ((S_8017085C_0 *)motion)->unk_12.s;
    if (state == 1) {
        goto timed_bob;
    }
    if (state < 2) {
        if (state == 0) {
            goto bob;
        }
        return;
    }
    if (state == 2) {
        goto settle;
    }
    return;

bob:
    frame = ((S_8017085C_0 *)motion)->unk_18;
    ((S_8017085C_0 *)motion)->unk_18 = frame + 1;
    phase = (s32)((u32)frame << 0x10);
    phase >>= 4;
    ((S_8017085C_0 *)motion)->unk_5C = (0 - func_800644B8(phase / 80)) << 7;
    height_offset = ((S_8017085C_0 *)motion)->unk_5C - 0x200000;
    ((S_8017085C_1 *)position)->unk_08.at00.v = ((S_8017085C_1 *)position)->unk_14 + height_offset;

    return;

timed_bob:
    frame = ((S_8017085C_0 *)motion)->unk_18;
    ((S_8017085C_0 *)motion)->unk_18 = frame + 1;
    phase = (s32)((u32)frame << 0x10);
    phase >>= 4;
    ((S_8017085C_0 *)motion)->unk_5C = (0 - func_800644B8(phase / 80)) << 7;
    height_offset = ((S_8017085C_0 *)motion)->unk_5C - 0x200000;
    ((S_8017085C_1 *)position)->unk_08.at00.v = ((S_8017085C_1 *)position)->unk_14 + height_offset;

    elapsed = ((S_8017085C_0 *)motion)->unk_18;
    ((S_8017085C_0 *)motion)->unk_18 = elapsed + 1;
    if ((s16)elapsed < 0x14) {
        return;
    }

    old_state = ((S_8017085C_0 *)motion)->unk_12.u;
    ((S_8017085C_0 *)motion)->unk_18 = 0;
    ((S_8017085C_0 *)motion)->unk_12.u = old_state + 1;
    return;

settle:
    ((S_8017085C_1 *)position)->unk_08.at00.v += 0x20000;
    if (((S_8017085C_1 *)position)->unk_08.at00.v < ((S_8017085C_1 *)position)->unk_14) {
        return;
    }

    ((S_8017085C_1 *)position)->unk_08.at00.v = ((S_8017085C_1 *)position)->unk_14;
    effect_args[1] = 0x12;
    effect_args[0] = 1;
    effect_args[2] = 0x32;
    effect_args[3] = 0;

    world_x = ((S_8017085C_1 *)position)->unk_02;
    if (world_x - 0x20 >= 0) {
        ((S_8017085C_0 *)motion)->unk_58 = (world_x - 0x20) >> 6;
    } else {
        ((S_8017085C_0 *)motion)->unk_58 = (world_x + 0x1F) >> 6;
    }

    world_z = ((S_8017085C_1 *)position)->unk_06;
    centered_z = world_z - 0x20;
    if (centered_z < 0) {
        centered_z = world_z + 0x1F;
    }
    tile_z = centered_z >> 6;
    ((S_8017085C_0 *)motion)->unk_59 = tile_z;
    func_800A7A7C(((S_8017085C_0 *)motion)->unk_58, (s8)tile_z,
        ((S_8017085C_1 *)position)->unk_08.at02.v, ((S_8017085C_2 *)effect)->unk_08, effect_args);

    (*(u16 *)((u8 *)motion + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;
}
