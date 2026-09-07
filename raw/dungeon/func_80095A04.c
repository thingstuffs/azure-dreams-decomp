#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 unk0[2];
    s32 unk8;
    s32 unkC[2];
    s32 unk14;
} Arg1;

typedef struct {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} Arg2;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009A350();
s16 func_800BCB04();

s32 func_8009B164(u32 arg0, Arg1 *arg1, Arg2 *arg2) {
    u16 sp10;
    Arg1 *temp_s2;
    Arg2 *temp_s1;
    s32 temp_s0;
    s32 temp_a0;
    s32 temp_a1;

    temp_s2 = arg1;
    temp_s1 = arg2;
    temp_s0 = (arg0 >> 9) & 7;
    if ((func_8009A350(temp_s1->x, temp_s1->y, temp_s0, &sp10) << 0x10) == 0) {
        goto return_one;
    }
    if (sp10 & 0x8000) {
        goto return_zero;
    }
    temp_a0 = temp_s1->x + D_8006CCD8[temp_s0];
    temp_a1 = temp_s1->y + D_8006CCE8[temp_s0];
    if (func_800BCB04((((s32) (temp_a0 << 0x10) >> 0xA) | 0x20) & 0xFFE0, (((s32) (temp_a1 << 0x10) >> 0xA) | 0x20) & 0xFFE0, (s32) (temp_s2->unk8 + (temp_s2->unk14 * 2)) >> 0x10) >= 0x200) {
        goto return_zero;
    }
return_one:
    return 1;
return_zero:
    return 0;
}
