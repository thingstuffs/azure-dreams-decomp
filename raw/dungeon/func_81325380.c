#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern s32 func_800AD9B4(void *, void *);
extern void func_8016CD88() __attribute__((noreturn));
extern void func_8016CDC0() __attribute__((noreturn));
extern void func_8016CE8C() __attribute__((noreturn));
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_8016B778[];
extern u8 D_8017467C[];
extern u8 D_80174684[];

void func_8016CB80(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *base1 ASM_REG("$18") = arg1;
    register void *base2 ASM_REG("$17") = arg2;
    register void *base3 ASM_REG("$19") = arg3;
    M2C_UNK sp18;
    s32 temp_a0;
    s32 temp_v1_2;
    s32 scaled;
    s32 delta;
    s32 temp_v1_3;
    u16 temp_v0;
    u16 temp_v1_4;
    s32 temp_v1;
    u8 *temp_a0_2;
    register void *temp_v1_dispatch ASM_REG("$3");
    register u32 temp_v0_page ASM_REG("$2");
    register u8 *temp_a1 ASM_REG("$5");

#define arg1 base1
#define arg2 base2
#define arg3 base3

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto block_10;
    }
    if ((s32) temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto block_0;
        }
        func_8016CDC0();
        return;
    }
    if (temp_v1 == 2) {
        goto block_14;
    }
    if (temp_v1 == 3) {
        goto block_18;
    }
    func_8016CDC0();
    return;
block_0:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
    M2C_FIELD(arg0, s16 *, 0x9E) = 5;
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_10:
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x9E);
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) - M2C_FIELD(arg0, s32 *, 0xA0));
    if (temp_a0 != 0) {
        scaled = M2C_FIELD(arg2, u8 *, 0x24);
        ASM_KEEP(scaled);
        delta = M2C_FIELD(arg1, s16 *, 2) - 0x20;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) (((scaled << 6) - delta) << 0x10) / temp_a0);
        delta = M2C_FIELD(arg1, s16 *, 6) - 0x20;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) (((M2C_FIELD(arg2, u8 *, 0x25) << 6) - delta) << 0x10) / (s16) M2C_FIELD(arg0, s16 *, 0x9E));
        M2C_FIELD(arg0, s32 *, 0xA0) = (s32) ((0 - func_800644B8(M2C_FIELD(arg0, s16 *, 0x9E) * 0x199)) << 0xA);
    }
    M2C_FIELD(arg0, s32 *, 0x90) = (s32) (M2C_FIELD(arg0, s32 *, 0x90) + M2C_FIELD(arg0, s32 *, 0xA0));
    temp_v1_2 = (u16) M2C_FIELD(arg0, s16 *, 0x9E) - 1;
    M2C_FIELD(arg0, s16 *, 0x9E) = temp_v1_2;
    if ((temp_v1_2 << 0x10) < 0) {
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x08000000);
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    }
block_14:
    if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x08000000) {
        M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
        func_8016CDC0();
        return;
    }
    goto block_22;
block_18:
    if (M2C_FIELD(arg0, u8 *, 0xB3) == 0) {
        temp_v1_dispatch = M2C_FIELD(arg2, void **, 0x2C);
        ASM_KEEP(temp_v1_dispatch);
        temp_v0_page = 0x80170000;
        ASM_KEEP(temp_v0_page);
        temp_a1 = (u8 *)temp_v0_page + 0x467C;
        ASM_TAILSLOT_PIN(temp_a1);
        func_8016CD88();
        return;
    }
    if (M2C_FIELD(arg2, u8 **, 0x2C) != D_80174684) {
        M2C_FIELD(arg2, u8 **, 0x2C) = D_80174684;
        func_80047784(arg2, D_80174684[((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    }
block_22:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        func_800A4ACC(arg3);
        temp_a0_2 = D_80083460;
        if (M2C_FIELD(temp_a0_2, s16 *, 8) != 0) {
            M2C_FIELD(temp_a0_2, s16 *, 8) = (s16) ((u16) M2C_FIELD(temp_a0_2, s16 *, 8) - 1);
        }
        temp_v1_3 = M2C_FIELD(arg3, s32 *, 0x1C);
        if (temp_v1_3 & 0x2000) {
            temp_v1_4 = M2C_FIELD(arg3, u16 *, 0x46);
            if (!(temp_v1_4 & 0x8000)) {
                goto block_32;
            }
            M2C_FIELD(arg3, u16 *, 0x46) = temp_v1_4 & 0x7FFF;
            func_8016CE8C(temp_a0_2);
            return;
        }
        if (temp_v1_3 & 0x410) {
            goto block_32;
        }
        if (!(temp_v1_3 & 0x20000)) {
            goto block_32;
        }
        M2C_FIELD(arg3, s16 *, 0x2A) = func_800A0818(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), D_80082E80[0x24], D_80082E80[0x25], &sp18);
block_32:
        if ((func_800AD9B4(arg2, arg3) << 0x10) > 0) {
            M2C_FIELD(arg0, u8 **, 0x8C) = D_8016B778;
            func_800A9A04(arg3);
        }
    }
}

#undef arg1
#undef arg2
#undef arg3

/* MECHANISM: The 0x38 frame holds arg0/arg1/arg2/arg3 in s0/s2/s1/s3, with the s3 copy in the first branch slot.
   Promoted temporaries and statement boundaries reproduce the signed loads, interpolation order, and countdown CFG.
   Restoring the state increment closed the three-word cascade; v1/page carriers plus the tail-slot pin close the dispatcher j. */
