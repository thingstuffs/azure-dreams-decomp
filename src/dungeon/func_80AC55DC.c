#include "common.h"
#include "shared/slus_callbacks.h"

typedef struct S_80AC55DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80AC55DC_0;   /* node in func_80AC55DC */

typedef struct S_80AC55DC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80AC55DC_1;   /* arg0 in func_80AC55DC */

typedef struct S_80AC55DC_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80AC55DC_2;   /* work in func_80AC55DC */

typedef struct S_80AC55DC_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80AC55DC_4;   /* sprite in func_80AC55DC */

typedef struct S_80AC55DC_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80AC55DC_5;   /* ((S_80AC55DC_0 *)node)->unk_08 in func_80AC55DC */

typedef struct S_80AC55DC_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80AC55DC_6;   /* ((S_80AC55DC_1 *)arg0)->unk_08 in func_80AC55DC */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

extern u8 D_800DEC70[];
extern u8 D_80170A84[];

/* Creates a sprite effect offset from its origin and initializes its return motion. */
void func_80AC55DC(
    S_80AC55DC_1 *origin, s16 effect_id, s32 effect_value, s16 duration,
    s32 offset_x, s32 offset_y, s32 offset_z)
{
    void *node;
    S_80AC55DC_2 *work;
    S_80AC55DC_4 *sprite;
    u16 sprite_flags;
    s32 step_x;
    s32 step_y;
    s32 step_z;
    s32 t;

    node = func_8003FC64(0x212);
    if (node != 0) {
        ((S_80AC55DC_0 *)node)->unk_10 = D_80170A84;

        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_02 =
            ((S_80AC55DC_6 *)(origin->unk_08))->unk_02 + offset_x;
        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_06 =
            ((S_80AC55DC_6 *)(origin->unk_08))->unk_06 + offset_y;
        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_0A =
            ((S_80AC55DC_6 *)(origin->unk_08))->unk_0A + offset_z - 0x14;

        work = (S_80AC55DC_2 *)((u8 *)node + 0x20);
        work->unk_36 = ((S_80AC55DC_6 *)(origin->unk_08))->unk_02;
        work->unk_38 = ((S_80AC55DC_6 *)(origin->unk_08))->unk_06;
        work->unk_3A = ((S_80AC55DC_6 *)(origin->unk_08))->unk_0A;
        step_x = -(offset_x << 16) / (duration / 8);
        work->unk_40 = step_x / 2;
        step_y = -(offset_y << 16) / (duration / 8);
        work->unk_44 = step_y / 2;
        step_z = -(offset_z << 16) / (duration / 8);
        t = step_z / 2;
        work->unk_48 = t;
        t = step_x;
        if (t < 0) {
            t += 3;
        }
        work->unk_4C = t >> 2;
        work->unk_50 = step_y / 4;
        work->unk_54 = step_z / 4;

        work->unk_14 = effect_id;
        work->unk_32 = duration;
        work->unk_34 = duration;
        func_8004491C(node, func_80045340);

        sprite = ((S_80AC55DC_0 *)node)->unk_0C;
        sprite_flags = sprite->unk_14;
        sprite->unk_10 = 0x20;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        sprite->unk_14 = sprite_flags | 0xC;
        ((S_80AC55DC_0 *)node)->unk_20 = effect_value;
        work->unk_08 = effect_value;
        func_8003DB94(sprite, D_800DEC70, 0);
    }
}

