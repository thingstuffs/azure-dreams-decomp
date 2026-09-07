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
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    u16 f14;
} State;

typedef struct {
    u8 pad0[0xC];
    s32 fc;
    s16 f10;
    s16 f12;
    u16 f14;
} Arg2State;

void func_800478B8();
s32 rand(void);
void func_800BBBE0(void *);
extern s32 D_800814A0[3];

void func_800BBA98(void *arg0, void *arg1, void *arg2) {
    s16 temp_v0_2;
    s16 temp_v1;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_a0;
    void *temp_a3;
    State *temp_s0;
    s32 var_a0;
    void *var_a1;
    register void *call_arg ASM_REG("$4") = arg0;
    register void *held_arg2 ASM_REG("$17") = arg2;

    temp_a3 = arg0;
    temp_s0 = (State *)arg1;
    temp_v1 = M2C_FIELD(temp_a3, s16 *, 0x4C);
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return func_800BBBE0(call_arg);
        }
        goto type1;
    }
zero_state:
    temp_s0->f0 += (temp_s0->fc / (s16) M2C_FIELD(temp_a3, s16 *, 0x48));
    temp_s0->f4 += (temp_s0->f10 / (s16) M2C_FIELD(temp_a3, s16 *, 0x48));
    temp_v0_2 = (u16) M2C_FIELD(temp_a3, s16 *, 0x48) - 1;
    M2C_FIELD(temp_a3, s16 *, 0x48) = temp_v0_2;
    temp_v1 = 0x60;
    if ((temp_v0_2 << 0x10) <= 0) {
        ((Arg2State *)held_arg2)->f10 = temp_v1;
        ((Arg2State *)held_arg2)->f14 |= 0xC;
        M2C_FIELD(temp_a3, u16 *, 0x4C) += 1;
        return func_800BBBE0(call_arg);
    }
    goto zero_shared;
type1:
        temp_s0->f0 += temp_s0->fc;
        temp_s0->f4 += temp_s0->f10;
        temp_v1_2 = temp_s0->fc;
        var_a0 = temp_v1_2 >> 1;
        temp_s0->fc = temp_v1_2 - var_a0;
        temp_s0->f10 -= (temp_s0->f10 >> 1);
        var_a1 = (void *)0xFFEFEFF0;
        ((Arg2State *)held_arg2)->fc += (s32)var_a1;
        if ((u8) ((Arg2State *)held_arg2)->fc < 0x11U) {
            M2C_FIELD(temp_a3, u16 *, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
        temp_v0 = (rand() & 7) << 0xF;
        temp_v1_3 = temp_s0->f8;
        temp_v1_3 -= temp_v0;
        temp_s0->f8 = temp_v1_3;
        func_800478B8(held_arg2);
        return;
zero_shared:
    temp_v0 = (rand() & 7) << 0xF;
    temp_v1_3 = temp_s0->f8;
    temp_v1_3 -= temp_v0;
    temp_s0->f8 = temp_v1_3;
    func_800478B8(held_arg2);
}
