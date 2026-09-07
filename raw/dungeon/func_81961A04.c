#include "common.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_FIELD_V(expr, type_ptr, offset) (*(volatile type_ptr)((s8 *)(expr) + (offset)))

void func_800272BC(void) __attribute__((noreturn));
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_80026DE4;
extern M2C_UNK D_800273B0;
extern M2C_UNK D_800CEEFC;

void *func_81961A04(void *arg0)
{
    void *temp_s3;
    s32 var_s1;
    M2C_UNK *temp_s5;
    M2C_UNK *temp_s4;
    register s32 temp_s2 ASM_REG("$18");
    void *temp_v0;
    register s32 arithmetic_v0 ASM_REG("$2");
    register s32 arithmetic_v1 ASM_REG("$3");
    register u16 reload_a0 ASM_REG("$4");
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    void *temp_a1;
    void *temp_a2;
    void *temp_v1;

    temp_s3 = arg0;
    var_s1 = 0;
    temp_s5 = &D_80026DE4;
    temp_s4 = &D_800273B0;
    temp_s2 = 8;
loop_1:
    temp_v0 = func_8003FC64(2);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = temp_s5;
        func_8004491C(temp_v0, &D_800CEEFC);
        temp_v1 = M2C_FIELD(temp_v0, void **, 8);
        temp_v0_2 = M2C_FIELD(temp_s3, u16 *, 2);
        temp_a2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, u16 *, 2) = temp_v0_2;
        M2C_FIELD(temp_v1, u16 *, 0xE) = temp_v0_2;
        M2C_FIELD(temp_a2, u16 *, 0x38) = temp_v0_2;
        temp_v0_3 = M2C_FIELD(temp_s3, u16 *, 6);
        M2C_FIELD(temp_v1, u16 *, 6) = temp_v0_3;
        M2C_FIELD(temp_v1, u16 *, 0x12) = temp_v0_3;
        M2C_FIELD(temp_a2, u16 *, 0x3A) = temp_v0_3;
        temp_v0_4 = M2C_FIELD(temp_s3, u16 *, 0xA);
        M2C_FIELD(temp_v1, u16 *, 0xA) = temp_v0_4;
        M2C_FIELD(temp_v1, u16 *, 0x16) = temp_v0_4;
        M2C_FIELD(temp_a2, u16 *, 0x3C) = temp_v0_4;
        temp_a1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_a1, M2C_UNK **, 8) = temp_s4;
        if (var_s1 != temp_s2) {
            arithmetic_v0 = 0x200;
            ASM_TAILSLOT_PIN(arithmetic_v0);
            func_800272BC();
            return (void *)0x200;
        }
        ASM_KEEP(temp_s2);
        do { M2C_FIELD(temp_a1, u16 *, 0x1E) = 0x800U; } while (0);
        arithmetic_v0 = (temp_s2 - var_s1) * 4;
        arithmetic_v1 = -0x80 - arithmetic_v0;
        reload_a0 = M2C_FIELD_V(temp_a1, u16 *, 0x1E);
        M2C_FIELD(temp_a1, s8 *, 0xC) = (s8)arithmetic_v1;
        M2C_FIELD(temp_a1, u16 *, 0x1C) = reload_a0;
        M2C_FIELD(temp_a2, s16 *, 0x54) = var_s1;
        if (var_s1 == temp_s2) {
            M2C_FIELD(temp_a2, s16 *, 0x54) = 7;
        }
        M2C_FIELD(temp_a2, s16 *, 0x4C) = temp_s2;
        goto block_8;
    }
block_8:
    var_s1 += 1;
    if (var_s1 < 9) {
        goto loop_1;
    }
    return temp_v0;
}
