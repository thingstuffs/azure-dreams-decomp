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

extern u8 D_800E3D40[];
s32 func_800990FC(void);
s32 func_80099194(void *, s32);
void func_80099290(s32);
s32 func_8009929C(s32, s32);
s32 func_8009955C(void *, s32);
void func_800A56E0(s32);
void func_800A5720(s32);
void func_800A6508(void);
s32 func_800A6D30();
void func_800C5BBC(s32, s32, s32, s32, s32, s32);
s32 func_800C80F0(void);
s32 func_800CE7F0();
s32 func_800CE8A0();
void func_800CE9C0(void) __attribute__((noreturn));

extern u8 D_800E1B76[18];
extern u8 D_800E1B87[18];
extern u8 D_800E1B99[18];
extern u8 D_800E1BAA[18];

s32 func_800CE748(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_s1;
    s32 var_s2;
    s32 temp_a0_3;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v1_2;

    var_s2 = 0;
    var_s1 = 0;
    if (func_800C80F0() == 0) {
        temp_s0 = M2C_FIELD(arg0, void **, 0x4C);
        if (temp_s0 != NULL) {
            s32 probability;

            probability = 0;
            var_s1 = 1;
            if (M2C_FIELD(temp_s0, u8 *, 1) == 0xF) {
                register s32 is_one ASM_REG("$2");

                is_one = M2C_FIELD(temp_s0, u8 *, 0) == 1;
                ASM_KEEP_NV(is_one);
                var_s1 = is_one;
            }
            if (*D_800E3D40 == 0) {
                temp_a0_2 = func_800A6D30() & 0xFFFF;
                if (M2C_FIELD(arg0, u8 *, 3) != 0) {
                    register s32 random_mod ASM_REG("$3");
                    random_mod = temp_a0_2 % M2C_FIELD(arg0, u8 *, 3);
                    ASM_KEEP(random_mod);
                    func_800CE7F0(temp_a0_2);
                    return random_mod;
                }
                goto block_9;
            }
block_9:
            if (probability < 0x40) {
                if (!(var_s1 & 1)) {
                    if (M2C_FIELD(temp_s0, s8 *, 2) >= -0x62) {
                        M2C_FIELD(temp_s0, s8 *, 2) = (s8) ((u8) M2C_FIELD(temp_s0, s8 *, 2) - 1);
                    }
                }
                var_s2 = 1;
            }
            goto block_13;
        }
block_13:
        temp_s0_2 = M2C_FIELD(arg0, void **, 0x50);
        if (temp_s0_2 != NULL) {
            s32 probability;

            probability = 0;
            temp_a0_3 = M2C_FIELD(temp_s0_2, u8 *, 0);
            temp_v1 = temp_a0_3 & 0xFF;
            if ((temp_v1 == 1) || (temp_v1 == 7) || (((u32) (temp_a0_3 - 2) < 2U) != 0)) {
                var_s1 |= 2;
            }
            if (*D_800E3D40 == 0) {
                temp_a0 = func_800A6D30(temp_a0_3) & 0xFFFF;
                if (M2C_FIELD(arg0, u8 *, 3) != 0) {
                    register s32 random_mod ASM_REG("$3");
                    random_mod = temp_a0 % M2C_FIELD(arg0, u8 *, 3);
                    ASM_KEEP(random_mod);
                    func_800CE8A0(temp_a0);
                    return random_mod;
                }
                goto block_23;
            }
block_23:
            if (probability < 0x40) {
                if (!(var_s1 & 2)) {
                    if (M2C_FIELD(temp_s0_2, s8 *, 2) >= -0x62) {
                        M2C_FIELD(temp_s0_2, s8 *, 2) = (s8) ((u8) M2C_FIELD(temp_s0_2, s8 *, 2) - 1);
                    }
                }
                var_s2 |= 2;
            }
            goto block_28;
        }
        goto block_28;
    }
block_28:
    if (M2C_FIELD(arg0, s32 *, 0x14) & 0x4000) {
        if ((var_s2 << 0x10) == 0) {
            register s32 dead_shift ASM_REG("$2");

            func_800A6508();
            ASM_SCHED_BARRIER();
            dead_shift = (u16) var_s2 << 0x10;
            ASM_TAILSLOT_PIN(dead_shift);
            func_800CE9C0();
        }
        temp_v0 = func_800990FC();
        var_a1 = temp_v0;
        if (var_s2 & 1) {
            temp_a1_2 = func_8009955C(M2C_FIELD(arg0, void **, 0x4C), var_a1);
            {
                register void *message ASM_REG("$4");

                if (!(var_s1 & 1)) {
                    message = D_800E1B76;
                } else {
                    message = D_800E1B87;
                }
                ASM_KEEP_NV(message);
                var_a1 = func_80099194(message, temp_a1_2);
            }
            if (var_s2 & 2) {
                var_a1 = func_8009929C(0xA, var_a1);
            }
        }
        if (var_s2 & 2) {
            temp_a1 = func_8009955C(M2C_FIELD(arg0, void **, 0x50), var_a1);
            {
                register void *message ASM_REG("$4");

                if (!(var_s1 & 2)) {
                    message = D_800E1B99;
                } else {
                    message = D_800E1BAA;
                }
                ASM_KEEP_NV(message);
                var_a1 = func_80099194(message, temp_a1);
            }
        }
        func_80099290(var_a1);
        func_800A5720(temp_v0);
    }
    if ((var_s2 << 0x10) != 0) {
        temp_v1_2 = M2C_FIELD(arg0, void **, -0x14);
        if (!(M2C_FIELD(temp_v1_2, u16 *, 0x14) & 0x8000)) {
            func_800C5BBC((M2C_FIELD(temp_v1_2, u8 *, 0x24) << 6) | 0x20, (M2C_FIELD(temp_v1_2, u8 *, 0x25) << 6) | 0x20, M2C_FIELD(arg0, s16 *, 0x88), 0xC0C040, 0x20, 0);
            func_800A56E0(0x615);
        }
    }
    return 1;
}
