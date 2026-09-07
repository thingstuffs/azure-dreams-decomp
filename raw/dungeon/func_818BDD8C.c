#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800256A0() __attribute__((noreturn));
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_800254E0;
extern M2C_UNK D_80025DF8;
extern M2C_UNK D_80045340;

void *func_818BDD8C(void *arg0, void *arg1)
{
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 other_flags;
    register s32 temp_v1_2 ASM_REG("$3");
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_4;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_800254E0;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_v1, s16 *, 0x10) = 0;
        M2C_FIELD(temp_v1, u16 *, 0x14) =
            (u16)M2C_FIELD(arg0, u16 *, 0x12);
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E01;
        M2C_FIELD(temp_s0, M2C_UNK **, 8) = &D_80025DF8;
        temp_v1_2 = M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC;
        other_flags = M2C_FIELD(temp_s0, u16 *, 0x10) | 0x20;
        ASM_SCHED_BARRIER();
        M2C_FIELD(temp_s0, u16 *, 0x14) = temp_v1_2;
        temp_v1_2 |= 0x100;
        M2C_FIELD(temp_s0, u16 *, 0x10) = other_flags;
        ASM_KEEP(temp_v1_2);
        M2C_FIELD(temp_s0, u16 *, 0x14) = temp_v1_2;
        {
            register void *call_obj ASM_REG("$4");
            register s32 scale ASM_REG("$2");

            M2C_FIELD(temp_s0, s16 *, 0x1A) =
                (s16)(rand() % 0x1000);
            call_obj = temp_v0;
            ASM_KEEP(call_obj);
            scale = 0x400;
            ASM_KEEP(scale);
            ASM_SCHED_BARRIER();
            M2C_FIELD(temp_s0, s16 *, 0x1E) = scale;
            M2C_FIELD(temp_s0, s16 *, 0x1C) = scale;
            func_8004491C(call_obj, &D_80045340);
        }
        temp_v1_4 = M2C_FIELD(temp_v0, void **, 8);
        ASM_KEEP(temp_v1_4);
        {
            register void *v0pin ASM_REG("$2");
            v0pin = temp_v0;
            ASM_KEEP(v0pin);
        }
        temp_a0 = M2C_FIELD(arg1, s32 *, 0);
        temp_a1 = M2C_FIELD(arg1, s32 *, 4);
        temp_a2 = M2C_FIELD(arg1, s32 *, 8);
        temp_a3 = M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_v1_4, s32 *, 0) = temp_a0;
        M2C_FIELD(temp_v1_4, s32 *, 4) = temp_a1;
        M2C_FIELD(temp_v1_4, s32 *, 8) = temp_a2;
        M2C_FIELD(temp_v1_4, s32 *, 0xC) = temp_a3;
        temp_a0 = M2C_FIELD(arg1, s32 *, 0x10);
        temp_a1 = M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(temp_v1_4, s32 *, 0x10) = temp_a0;
        M2C_FIELD(temp_v1_4, s32 *, 0x14) = temp_a1;
        func_800256A0(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}

/* MECHANISM: The natural 0x20 frame holds arg0/object/arg1 in s0/s1/s2.
   A v1 flags accumulator plus a separate v0 flags word prevents OR fusion;
   pinned a0/v0 lifetimes and a fence place li before the callback la pair,
   while the kept destination and v0 result preserve the retail tail ABI. */
