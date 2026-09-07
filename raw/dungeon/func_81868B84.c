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

M2C_UNK func_80024264();
extern void func_8002465C(void) __attribute__((noreturn));
extern void func_80024660(void) __attribute__((noreturn));
s32 func_800644B8();
s32 func_80064584();
s32 func_800A45D8();
extern s32 D_800814A0[];

void func_81868B84(void *arg0, void *arg1) {
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s0_2;
    register s32 var_s3 ASM_REG("$19");
    register s32 var_s3_2 ASM_REG("$19");
    register s32 var_s4 ASM_REG("$20");
    register s32 var_s4_2 ASM_REG("$20");
    register s32 state3_compare ASM_REG("$2");
    u16 temp_v0_2;
    void *temp_v0;
    s16 state;

    temp_v0 = M2C_FIELD(arg0, void **, 0xC);
    M2C_FIELD(temp_v0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_v0, u16 *, 0x14) + 1);
    M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 1);
    state = *(s16 *)arg0;
    if (state == 1) {
        goto state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0;
        }
        M2C_FIELD(arg0, u16 *, 0) = 3;
        func_80024660();
        return;
    }
    if (state == 2) {
        goto state2;
    }
    state3_compare = 3;
    ASM_KEEP(state3_compare);
    if (state == state3_compare) {
        goto state3;
    }
    M2C_FIELD(arg0, u16 *, 0) = 3;
    func_80024660();
    return;

state0:
        M2C_FIELD(arg1, u16 *, 0xA) = (u16) (M2C_FIELD(arg1, u16 *, 0xA) - 4);
        func_80024264(M2C_FIELD(arg0, void **, 0xC), arg1, M2C_FIELD(arg0, u8 *, 0x10));
        if (M2C_FIELD(arg0, s16 *, 2) < 8) {
            return;
        }
        {
            register s32 tail_value ASM_REG("$2");
            tail_value = M2C_FIELD(arg0, u16 *, 0) + 1;
            M2C_FIELD(arg0, u16 *, 2) = 0U;
            ASM_TAILSLOT_PIN(tail_value);
            func_8002465C();
        }
        return;
state1:
        var_s3_2 = 0;
        var_s4_2 = var_s3_2;
        M2C_FIELD(arg0, u16 *, 6) = (u16) (M2C_FIELD(arg0, u16 *, 6) + 6);
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 0xA) + 0x10;
        M2C_FIELD(arg0, u16 *, 0xA) = temp_v0_2;
        M2C_FIELD(arg0, u16 *, 8) = (u16) (M2C_FIELD(arg0, u16 *, 8) + temp_v0_2);
        do {
            temp_s0_2 = var_s4_2 >> 0x10;
            temp_lo = (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 8) + temp_s0_2) >> 4) * (s16) M2C_FIELD(arg0, u16 *, 6);
            M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 0xE) + (temp_lo >> 8));
            temp_lo = (func_80064584((s16) M2C_FIELD(arg0, u16 *, 8) + temp_s0_2) >> 4) * (s16) M2C_FIELD(arg0, u16 *, 6);
            M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 0x12) + (temp_lo >> 8));
            if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA), temp_lo) << 0x10) == 0) {
                func_80024264(M2C_FIELD(arg0, void **, 0xC), arg1, M2C_FIELD(arg0, u8 *, 0x10));
            }
            var_s4_2 += 0x05550000;
            var_s3_2 += 1;
        } while (var_s3_2 < 3);
        if (M2C_FIELD(arg0, s16 *, 2) < 0x20) {
            return;
        }
        {
            register s32 tail_value ASM_REG("$2");
            tail_value = M2C_FIELD(arg0, u16 *, 0) + 1;
            M2C_FIELD(arg0, u16 *, 2) = 0U;
            ASM_TAILSLOT_PIN(tail_value);
            func_8002465C();
        }
        return;
state2:
        var_s3 = 0;
        var_s4 = var_s3;
        M2C_FIELD(arg0, u16 *, 6) = (u16) (M2C_FIELD(arg0, u16 *, 6) + 6);
        M2C_FIELD(arg0, u16 *, 8) = (u16) (M2C_FIELD(arg0, u16 *, 8) + M2C_FIELD(arg0, u16 *, 0xA));
        do {
            temp_s0 = var_s4 >> 0x10;
            temp_lo = (func_800644B8((s16) M2C_FIELD(arg0, u16 *, 8) + temp_s0) >> 4) * (s16) M2C_FIELD(arg0, u16 *, 6);
            M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 0xE) + (temp_lo >> 8));
            temp_lo = (func_80064584((s16) M2C_FIELD(arg0, u16 *, 8) + temp_s0) >> 4) * (s16) M2C_FIELD(arg0, u16 *, 6);
            M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 0x12) + (temp_lo >> 8));
            if ((func_800A45D8(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) M2C_FIELD(arg1, u16 *, 0xA), temp_lo) << 0x10) == 0) {
                func_80024264(M2C_FIELD(arg0, void **, 0xC), arg1, M2C_FIELD(arg0, u8 *, 0x10));
            }
            var_s4 += 0x05550000;
            var_s3 += 1;
        } while (var_s3 < 3);
        M2C_FIELD(arg0, u8 *, 0x10) = (u8) (M2C_FIELD(arg0, u8 *, 0x10) - 8);
        if (M2C_FIELD(arg0, s16 *, 2) < 8) {
            return;
        }
        {
            register s32 tail_value ASM_REG("$2");
            tail_value = M2C_FIELD(arg0, u16 *, 0) + 1;
            M2C_FIELD(arg0, u16 *, 2) = 0U;
            ASM_TAILSLOT_PIN(tail_value);
            func_8002465C();
        }
        return;
state3:
        ASM_SCHED_BARRIER();
        M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), s8 *, 0x16) = 1;
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        {
            register s32 *state3_global ASM_REG("$3");
            state3_global = D_800814A0;
            state3_global[0] |= 0x8000;
        }
        M2C_FIELD(arg0, u16 *, 0) = (u16) ((s32 (*)(void)) func_80024660)();
}
