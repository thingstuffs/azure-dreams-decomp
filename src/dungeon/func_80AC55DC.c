#include "common.h"

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
    volatile s32 unk_40;
    volatile s32 unk_44;
    volatile s32 unk_48;
    s32 unk_4C;
    s32 unk_50;
    s32 unk_54;
} S_80AC55DC_2;   /* work in func_80AC55DC */

typedef struct S_80AC55DC_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80AC55DC_3;   /* source in func_80AC55DC */

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

extern s32 D_80045340;
extern u8 D_800DEC70[];
extern u8 D_80170A84[];

void func_80AC55DC(
    S_80AC55DC_1 *arg0, s16 arg1, s32 arg2, s16 arg3,
    s32 arg4, s32 arg5, s32 arg6)
{
    void *node;
    S_80AC55DC_2 *work;
    S_80AC55DC_4 *sprite;
    S_80AC55DC_3 *source;
    u16 third;
    u16 flags;
    s32 size;
    void *data;
    s32 div_raw;
    s32 numerator;
    s32 divisor;
    register s32 adjusted ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 step_x ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 step_y ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 step_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    node = func_8003FC64(0x212);
    if (node != 0) {
        ((S_80AC55DC_0 *)node)->unk_10 = D_80170A84;

        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_02 =
            ((S_80AC55DC_6 *)(arg0->unk_08))->unk_02 + arg4;
        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_06 =
            ((S_80AC55DC_6 *)(arg0->unk_08))->unk_06 + arg5;
        ((S_80AC55DC_5 *)(((S_80AC55DC_0 *)node)->unk_08))->unk_0A =
            ((S_80AC55DC_6 *)(arg0->unk_08))->unk_0A + arg6 - 0x14;

        work = (u8 *)node + 0x20;
        work->unk_36 = ((S_80AC55DC_6 *)(arg0->unk_08))->unk_02;
        work->unk_38 = ((S_80AC55DC_6 *)(arg0->unk_08))->unk_06;
        div_raw = arg3 << 16;
        source = arg0->unk_08;
        divisor = div_raw >> 16;
        third = source->unk_0A;
        adjusted = divisor;
        work->unk_3A = third;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        numerator = arg4 << 16;
        numerator = -numerator;
        if (divisor < 0) {
            adjusted = divisor + 7;
        }
        adjusted >>= 3;

        step_x = numerator / adjusted;
        work->unk_40 = step_x / 2;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        numerator = arg5 << 16;
        numerator = -numerator;
        step_y = numerator / adjusted;
        work->unk_44 = step_y / 2;
        ASM_KEEP(adjusted);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        step_z = -(arg6 << 16) / adjusted;
        work->unk_48 = step_z / 2;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

        work->unk_4C = step_x / 4;
        ASM_KEEP(step_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work->unk_50 = step_y / 4;
        ASM_KEEP(step_y);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(step_z);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        work->unk_54 = step_z / 4;

        work->unk_14 = arg1;
        work->unk_32 = arg3;
        work->unk_34 = arg3;
        func_8004491C(node, &D_80045340);

        data = D_800DEC70;
        ASM_KEEP(data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        sprite = ((S_80AC55DC_0 *)node)->unk_0C;
        size = 0x20;
        flags = sprite->unk_14;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        sprite->unk_10 = size;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0;
        sprite->unk_0D = 0;
        sprite->unk_0C = 0;
        sprite->unk_14 = flags | 0xC;
        ((S_80AC55DC_0 *)node)->unk_20 = arg2;
        work->unk_08 = arg2;
        func_8003DB94(sprite, data, 0);
    }
}

/* MECHANISM: The seven live arguments naturally produce the retail 0x38 frame and saved-register order.
   Split pinned $v0 numerators from $a2/$a1/$v1 quotients; narrow barriers preserve each mflo/round/store seam.
   A one-read flags RMW plus held $a1 data pointer fixes the final li/lhu/zero-argument schedule. */
