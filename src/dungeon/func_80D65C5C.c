#include "common.h"


typedef s32 M2C_UNK;

typedef struct S_80D65C5C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D65C5C_0;   /* node in func_80D65C5C */

typedef struct S_80D65C5C_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80D65C5C_1;   /* arg0 in func_80D65C5C */

typedef struct S_80D65C5C_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} S_80D65C5C_2;   /* sprite in func_80D65C5C */

typedef struct S_80D65C5C_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80D65C5C_3;   /* part in func_80D65C5C */

typedef struct S_80D65C5C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80D65C5C_4;   /* ((S_80D65C5C_0 *)node)->unk_08 in func_80D65C5C */

typedef struct S_80D65C5C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D65C5C_5;   /* ((S_80D65C5C_1 *)arg0)->unk_08 in func_80D65C5C */

typedef struct S_80D65C5C_6 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80D65C5C_6;   /* ((S_80D65C5C_0 *)node)->unk_0C in func_80D65C5C */


extern void *func_8003FC64(s32, s32);
extern s32 rand(void);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 D_80045340;
extern M2C_UNK D_800DE870;
extern s16 D_800E2468[];
extern u8 D_80171384[];

/* Spawns a directional sprite effect near the source with randomized velocity. */
void func_80D65C5C(S_80D65C5C_1 *source, s32 angle)
{
    void *node;
    S_80D65C5C_2 *sprite;
    s16 *direction_step;

    node = func_8003FC64(0x212, angle);
    if (node != 0) {
        ((S_80D65C5C_0 *)node)->unk_10 = D_80171384;

        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_02 =
            ((S_80D65C5C_5 *)(source->unk_08))->unk_02;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_06 =
            ((S_80D65C5C_5 *)(source->unk_08))->unk_06;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_0A =
            ((S_80D65C5C_5 *)(source->unk_08))->unk_0A - 0x58;

        direction_step = (s16 *)((u8 *)D_800E2468 + (((u32)angle >> 7) & 0x1C));
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_02 += direction_step[0] * 0x12;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_06 += direction_step[1] * 0x12;

        ((S_80D65C5C_6 *)(((S_80D65C5C_0 *)node)->unk_0C))->unk_06 = 6;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_0C =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_10 =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_14 =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;

        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_0C +=
            direction_step[0] * 0x1C0000;
        ((S_80D65C5C_4 *)(((S_80D65C5C_0 *)node)->unk_08))->unk_10 +=
            direction_step[1] * 0x1C0000;

        sprite = (u8 *)node + 0x20;
        sprite->unk_0A = angle;
        sprite->unk_0C = 0xC;
        sprite->unk_0E = 0xC;
        func_8004491C(node, &D_80045340);

        {
            S_80D65C5C_3 *part = ((S_80D65C5C_0 *)node)->unk_0C;

            part->unk_14 |= 0xC;
            part->unk_10 = 0x60;
            part->unk_14 |= 2;
            part->unk_1C = 0x800;
            part->unk_1E = 0x800;
            part->unk_0E = 0x80;
            part->unk_0D = 0x80;
            part->unk_0C = 0x80;
            part->unk_14 |= 0x100;
            part->unk_12 = 0x7DCF;
            func_8003DB94(part, &D_800DE870, 0);
        }
    }
}
