#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80024D10(void) __attribute__((noreturn));
s32 func_8003DB94();
s32 func_800478B8();
s32 func_800644B8();
s32 func_80064584();
extern s32 D_800814A0[3];
extern M2C_UNK D_800DEC70[3];

void func_818BD3B0(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0_2;
    s32 temp_lo;
    s32 temp_v1_2;
    u16 temp_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0);
    M2C_FIELD(temp_v1, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v1, u16 *, 0x14) + 1);
    temp_v0 = M2C_FIELD(arg0, u16 *, 4) + 1;
    M2C_FIELD(arg0, u16 *, 4) = temp_v0;
    if (M2C_FIELD(arg0, s16 *, 6) < (s16) temp_v0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        func_80024D10();
        return;
    }
    temp_v1_2 = (s32) ((func_80064584((s16) temp_v0 << 7) >> 4) * M2C_FIELD(arg0, s16 *, 0xA)) >> 8;
    M2C_FIELD(arg0, s16 *, 8) = (s16) temp_v1_2;
    M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) - (temp_v1_2 << 0x10));
    temp_lo = (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 4) << 7) >> 4) * M2C_FIELD(arg0, s16 *, 0xA);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xC) + 0x80;
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) temp_v0_2;
    M2C_FIELD(arg0, s16 *, 8) = (s16) (temp_lo >> 8);
    M2C_FIELD(arg1, s32 *, 0) = (s32) (M2C_FIELD(arg1, s32 *, 0xC) + (((func_80064584(temp_v0_2) >> 4) * M2C_FIELD(arg0, s16 *, 8)) << 8));
    M2C_FIELD(arg1, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 0x10) + (((func_800644B8((s16) M2C_FIELD(arg0, u16 *, 0xC)) >> 4) * M2C_FIELD(arg0, s16 *, 8)) << 8));
    func_800478B8(arg2);
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        func_8003DB94(arg2, &D_800DEC70, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame and s0/s2/s1 lifetime shape.
   The zero-argument func_80024D10 edge is noreturn, enabling LEAD 18 to replace
   jal-plus-epilogue with retail's tail j while retaining the global store slot. */
