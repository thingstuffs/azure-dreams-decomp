#include "common.h"

typedef unsigned long long u64;

typedef struct S_80172920_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172920_0;   /* arg3 in func_80172920 */

typedef struct S_80172920_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80172920_1;   /* flags in func_80172920 */

typedef struct S_80172920_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172920_2;   /* arg2 in func_80172920 */

typedef struct S_80172920_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172920_3;   /* arg0 in func_80172920 */



extern s32 D_80083460;

extern void func_8009C93C(void *, void *, s16, s32, s32);
extern s32 func_800A0134(s32, void *);
extern s32 func_800A04F0(void *, u8, u8, s16);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, s32);
extern void func_800C7930(void *, s32, s32, s32);

s32 func_80172920(S_80172920_3 *arg0, s32 arg1, S_80172920_2 *arg2, void *arg3) {
    volatile u64 frame_pad;
    s32 result;
    s32 *flags;

    ((S_80172920_0 *)arg3)->unk_71 &= 0x7F;
    flags = &D_80083460;

    if (((S_80172920_1 *)flags)->unk_02 & 0x2000) {
        goto shared_failure;
    }

    result = func_800A04F0(
        arg3,
        arg2->unk_24,
        arg2->unk_25,
        ((S_80172920_0 *)arg3)->unk_2A);

    if ((func_800A2CB8(arg3, result) << 16) == 0) {
        return 0;
    }

    if (((S_80172920_1 *)flags)->unk_02 & 0x2000) {
        return -1;
    }

    if (!(((S_80172920_0 *)arg3)->unk_46 & 0x8000) &&
        (((S_80172920_1 *)flags)->unk_02 & 8)) {
        return -1;
    }

    if ((u32)(((0 - func_800A0134(result, arg3)) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }

    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);

    if ((func_800A2B5C(arg3) << 16) == 0) {
        goto success;
    }

shared_failure:
    return -1;

success:
    arg0->unk_9A = 0x11;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    ((S_80172920_0 *)arg3)->unk_84 = 0x7C;
    ((S_80172920_0 *)arg3)->unk_85 = 4;
    ((S_80172920_0 *)arg3)->unk_6D--;

    func_8009C93C(arg3, arg2, ((S_80172920_0 *)arg3)->unk_2A, 1, 0);
    return 1;
}

/* MECHANISM: An unused volatile u64 frame object plus the natural long-lived
   args/result/global base produce the retail 0x40 frame and s0-s5 roles.
   A shared mid-function failure block restores both branch targets and polarity;
   explicit (0 - call) + 0x40 emits retail's negu/addiu arithmetic in v0. */
