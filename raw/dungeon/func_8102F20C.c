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
typedef struct {
    u16 x0;
    u16 x1;
    u16 x2;
} Stack3;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s8 D_800DCECC[];
extern s16 D_80083228[5];
extern s32 D_800814A0[3];
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800478B8(void *, s32);

void func_8102F20C(void *arg0, void *arg1, void *arg2) {
    Stack3 sp10;
    M2C_UNK sp24;
    M2C_UNK sp20;
    M2C_UNK sp18[2];
    s16 temp_s0;
    s32 temp_a1;
    void *temp_v1;
    void *out;

    out = arg2;
    sp10.x0 = M2C_FIELD(arg1, u16 *, 2);
    sp10.x1 = M2C_FIELD(arg1, u16 *, 6);
    sp10.x2 = M2C_FIELD(arg1, u16 *, 0xA);
    temp_s0 = func_80065420(&sp10.x0, &sp18, &sp20, &sp24);
    temp_v1 = M2C_FIELD(arg0, void **, 0x28);
    sp10.x0 = M2C_FIELD(temp_v1, u16 *, 2);
    sp10.x1 = M2C_FIELD(temp_v1, u16 *, 6);
    sp10.x2 = M2C_FIELD(temp_v1, u16 *, 0xA);
    temp_s0 = temp_s0 - func_80065420(&sp10.x0, &sp18, &sp20, &sp24);
    temp_a1 = D_800DCECC[((s32) (*D_80083228 + M2C_FIELD(arg0, s16 *, 0x1C) + 0x100) >> 9) & 7] * 2;
    temp_s0 = temp_s0 + temp_a1;
    M2C_FIELD(out, u16 *, 0x14) = (u16) (M2C_FIELD(out, u16 *, 0x14) & 0xFF7F);
    M2C_FIELD(out, s16 *, 6) = temp_s0;
    func_800478B8(out, temp_a1);
    if (M2C_FIELD(out, u16 *, 0x14) & 0x6000) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
