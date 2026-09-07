#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DB420;

void func_800DB2DC(void *arg0, void *arg1, void *arg2, s16 arg3) {
    register M2C_UNK *held_callback;
    register s32 held_scale ASM_REG("$21");
    register void *held_arg0 ASM_REG("$18");
    register void *held_arg1 ASM_REG("$19");
    register void *held_arg2 ASM_REG("$23");
    register s16 held_arg3 ASM_REG("$20");
    register s32 var_s0 ASM_REG("$16");
    register s32 var_s1 ASM_REG("$17");
    u16 temp_v0;
    u16 temp_u16;
    s32 temp_s32;
    void *temp_a0;
    void *temp_v1;
    void *var_a2;

    var_a2 = arg2;
    held_arg0 = arg0;
    held_arg1 = arg1;
    held_arg2 = arg2;
    held_arg3 = arg3;
    var_s1 = 3;
    held_callback = &D_800DB420;
    held_scale = 0x1000;
    do {
        var_s0 = 3;
        do {
        var_a2 = func_8003FD64(0x312, &D_80083498, var_a2);
        if (var_a2 != 0) {
            M2C_FIELD(var_a2, M2C_UNK **, 0x10) = held_callback;
            temp_a0 = M2C_FIELD(var_a2, void **, 0xC);
            M2C_FIELD(var_a2, u16 *, 0x4A) =
                (u16)M2C_FIELD(held_arg2, u16 *, 0x2A);
            temp_s32 = M2C_FIELD(held_arg1, s32 *, 0x28);
            M2C_FIELD(temp_a0, s16 *, 0x1E) = held_scale;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = held_scale;
            M2C_FIELD(temp_a0, s32 *, 0x28) = temp_s32;
            temp_v0 = M2C_FIELD(held_arg1, u16 *, 0x14);
            M2C_FIELD(temp_a0, u16 *, 0x14) = temp_v0;
            temp_u16 = M2C_FIELD(held_arg1, u16 *, 0x12);
            M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
            M2C_FIELD(temp_a0, u16 *, 0x14) = (u16)(temp_v0 | 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x12) =
                (s16)(temp_u16 - 0x80);
            M2C_FIELD(var_a2, void **, 0x20) = held_arg0;
            M2C_FIELD(M2C_FIELD(var_a2, void **, 8), u16 *, 2) =
                (u16)M2C_FIELD(held_arg0, u16 *, 2);
            M2C_FIELD(M2C_FIELD(var_a2, void **, 8), u16 *, 6) =
                (u16)M2C_FIELD(held_arg0, u16 *, 6);
            M2C_FIELD(M2C_FIELD(var_a2, void **, 8), u16 *, 0xA) =
                (u16)M2C_FIELD(held_arg0, u16 *, 0xA);
            temp_v1 = var_a2 + 0x20;
            M2C_FIELD(temp_v1, s16 *, 6) = held_arg3;
            M2C_FIELD(temp_v1, s16 *, 4) = (s16)(var_s1 != 0);
            M2C_FIELD(temp_a0, s32 *, 0x2C) =
                (s32)M2C_FIELD(held_arg1, s32 *, 0x2C);
        }
        ASM_KEEP(var_s0);
        } while (--var_s0 >= 0);
        var_s1 -= 3;
    } while (var_s1 >= 0);
    ASM_KEEP(held_scale);
    ASM_KEEP(held_arg0);
    ASM_KEEP(held_arg1);
    ASM_KEEP(held_arg2);
    ASM_KEEP(held_arg3);
    ASM_KEEP(var_s1);
}

/* MECHANISM: A 0x38 frame follows from pinned long-lived args/bases and two nested loop counters.
   Nested do loops independently initialize s1/s0, fixing the ra/s0 save order and loop delay slots.
   Split +0x28 word and +0x12 halfword live ranges preserve retail scheduling without extra nops. */
