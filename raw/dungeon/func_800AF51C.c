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

extern u8 D_80083498[];
void *func_8003FD64();
M2C_UNK func_8004E298();
M2C_UNK func_8004E5A0();
M2C_UNK func_8004E634();
s32 func_80069E98();
M2C_UNK func_800B1320();
void *func_800B1484();
M2C_UNK func_800B13CC();
extern M2C_UNK D_800B45E0;
extern M2C_UNK D_800B490C;
extern M2C_UNK D_800DF24C[];

typedef struct {
    u8 bytes[16];
    u16 arg3;
} StackLocal;

void *func_800B4C7C(s32 arg0, u8 *arg1, s16 arg2, u16 arg3) {
    StackLocal local;
    void *callback;
    void *call_a0;
    u8 *call_a1;
    s32 call_a2;
    s16 temp_v0_8;
    register u16 temp_t0 ASM_REG("$8");
    register s32 temp_cmp ASM_REG("$2");
    s32 temp_v1;
    register s32 temp_a3 ASM_REG("$7");
    register s32 temp_a0 ASM_REG("$4");
    register s32 temp_s6 ASM_REG("$22");
    register s32 temp_s4 ASM_REG("$20");
    void *temp_s7;
    s16 temp_s8;
    register void *temp_s5 ASM_REG("$21");
    s8 *temp_s0;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_s0_2;
    register void *temp_s3 ASM_REG("$19");
    void *temp_s2;
    void *temp_v0;
    register void *temp_v0_2 ASM_REG("$2");
    void *temp_v0_3;
    void *temp_v0_4;
    register void *temp_v1_ptr ASM_REG("$3");

    local.arg3 = arg3;
    temp_v0 = func_8003FD64(0x212, D_80083498);
    temp_s7 = (void *)(u32) arg0;
    ASM_KEEP(temp_s7);
    temp_s5 = temp_v0;
    if (temp_s5 != NULL) {
        temp_s8 = arg2;
        ASM_KEEP(temp_s8);
        temp_a0_2 = M2C_FIELD(temp_s5, void **, 8);
        temp_a1 = M2C_FIELD(temp_s5, void **, 0xC);
        temp_v0_3 = arg1 - 0x20;
        M2C_FIELD(temp_s5, void **, 0x20) = temp_v0_3;
        temp_v0_4 = M2C_FIELD(temp_v0_3, void **, 8);
        temp_s2 = temp_s5 + 0x20;
        M2C_FIELD(temp_s2, void **, 0x14) = temp_v0_4;
        temp_v0_5 = M2C_FIELD(temp_v0_4, u16 *, 2);
        M2C_FIELD(temp_a0_2, u16 *, 2) = temp_v0_5;
        temp_v1_ptr = M2C_FIELD(temp_s2, void **, 0x14);
        M2C_FIELD(temp_s2, u16 *, 0x18) = temp_v0_5;
        temp_v0_6 = M2C_FIELD(temp_v1_ptr, u16 *, 6);
        temp_a3 = 0x20;
        M2C_FIELD(temp_a0_2, u16 *, 6) = temp_v0_6;
        temp_v1_ptr = M2C_FIELD(temp_s2, void **, 0x14);
        ASM_SCHED_BARRIER();
        temp_s4 = arg0 & 0xF;
        ASM_KEEP(temp_s4);
        M2C_FIELD(temp_s2, u16 *, 0x1A) = temp_v0_6;
        temp_v0_7 = M2C_FIELD(temp_v1_ptr, u16 *, 0xA);
        temp_s6 = temp_s4;
        M2C_FIELD(temp_a0_2, u16 *, 0xA) = temp_v0_7;
        M2C_FIELD(temp_s2, u16 *, 0x1C) = temp_v0_7;
        ASM_SCHED_BARRIER();
        temp_v0_2 = temp_s5 + 0x40;
        ASM_KEEP(temp_v0_2);
        temp_s3 = temp_v0_2;
        ASM_KEEP(temp_s3);
        M2C_FIELD(temp_a1, void **, 8) = temp_v0_2;
        M2C_FIELD(temp_a1, s16 *, 6) = temp_a3;
        if (arg0 & 0x8000) {
            M2C_FIELD(temp_s2, s16 *, 0xE) = 1;
        }
        temp_a0 = arg0 & 0xF0;
        temp_v1 = (s16) arg2;
        if (temp_v1 >= 0) {
            arg0 = 0x50;
            temp_s0 = (s8 *) local.bytes;
            switch (temp_a0) {
            case 0x10:
                temp_v0_8 = 0x7F;
                goto store_and_advance;
            case 0x20:
                temp_v0_8 = 0x80;
                goto store_and_advance;
            case 0x30:
                local.bytes[0] = 0x2B;
                goto mode_check;
            case 0x40:
                temp_v0_8 = 0x2D;
                goto store_and_advance;
            case 0x50:
                local.bytes[0] = 0x81;
                goto mode_check;
            case 0x60:
                local.bytes[0] = 0x82;
                goto advance_buffer;
store_and_advance:
                local.bytes[0] = temp_v0_8;
advance_buffer:
                temp_s0 = (s8 *) local.bytes + 1;
                goto mode_check;
            case 0x80:
                func_8004E634(temp_v1, temp_s0);
                temp_s0 = (s8 *) temp_s0 + func_80069E98(temp_s0);
                *temp_s0++ = 0x45;
                *temp_s0++ = 0x58;
                *temp_s0++ = arg0;
                *temp_s0++ = 0;
                func_8004E298(temp_s3, local.bytes, temp_s4);
                goto mode_check;
            case 0xA0:
                local.bytes[0] = temp_a3;
                func_8004E5A0(temp_v1, 3, local.bytes + 1);
                temp_s0 = (s8 *) local.bytes + 6;
                local.bytes[4] = 0x25;
                local.bytes[5] = 0;
                func_8004E298(temp_s3, local.bytes, temp_s4);
                goto mode_check;
            case 0x90:
                func_8004E5A0(temp_v1, 4, temp_s0);
                temp_s0 = (s8 *) local.bytes + 6;
                local.bytes[4] = 0x47;
                local.bytes[5] = 0;
                func_8004E298(temp_s3, local.bytes, temp_s4);
                goto mode_check;
            default:
                goto mode_check;
            }
mode_check:
            if (((u32) temp_s7 & 0xF0) < 0x80U) {
                func_8004E5A0(temp_s8, 3, temp_s0);
                func_8004E298(temp_s3, local.bytes, temp_s6);
            }
            goto block_46;
        }
        temp_v0_8 = ~arg2;
        if (temp_v0_8 > 0) {
            M2C_FIELD(temp_s2, s16 *, 0x10) = 0x18;
        }
        func_8004E298(temp_s3, D_800DF24C[temp_v0_8], temp_s4);
        goto block_46;
block_46:
        temp_t0 = *(volatile u16 *) &local.arg3;
        temp_cmp = (s16) temp_t0;
        if (temp_cmp == 1) {
            callback = &D_800B490C;
        } else {
            callback = &D_800B45E0;
        }
        M2C_FIELD(temp_s5, void * volatile *, 0x10) = callback;
        ASM_SCHED_BARRIER();
        temp_s0_2 = temp_s2 + 0x20;
        func_800B1320(temp_s0_2, 0x80 - ((s32) (M2C_FIELD(func_800B1484(temp_s3), s8 *, 2) + 0x88) / 2), (s16) ((0 - (s8) M2C_FIELD(temp_s2, u8 *, 0x23)) - 4));
        func_800B13CC(temp_s0_2, 0x20);
    }
    return temp_s5;
}
