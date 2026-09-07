#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800244D4() __attribute__((noreturn));
s32 func_8003DB94();
void *func_8003FC64();
s32 func_8004491C();
s32 rand();
extern s32 D_80024264;
extern s32 D_800D36D0;
extern s32 D_800DEF08;

s32 func_800243BC(s32 arg0, void *arg1)
{
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0_2;
    s32 var_a2;
    register s32 return_value ASM_REG("$2");
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_3;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, s32 **, 0x10) = &D_80024264;
        M2C_FIELD(temp_v1, s32 *, 8) = arg0;
        M2C_FIELD(temp_v0, s16 *, 0x20) = 0;
        M2C_FIELD(temp_v1, s16 *, 2) = 0;
        M2C_FIELD(temp_v1, s16 *, 4) = 0x10;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E02;
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0;
        M2C_FIELD(temp_s0, s8 *, 0xC) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0;
        M2C_FIELD(temp_s0, u16 *, 0x14) =
            (s16)(M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        M2C_FIELD(temp_s0, u16 *, 0x10) =
            (u16)(M2C_FIELD(temp_s0, u16 *, 0x10) | 0x20);
        M2C_FIELD(temp_s0, u16 *, 0x14) =
            (u16)(M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
        temp_v0_2 = rand();
        var_a2 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_a2 = temp_v0_2 + 0xF;
        }
        func_8003DB94(temp_s0, &D_800DEF08,
                      (s16)(temp_v0_2 - ((var_a2 >> 4) * 0x10)));
        func_8004491C(temp_v0, &D_800D36D0);
        temp_v1_3 = M2C_FIELD(temp_v0, void **, 8);
        ASM_KEEP(temp_v1_3);
        return_value = (s32)temp_v0;
        ASM_KEEP(return_value);
        temp_a0 = M2C_FIELD(arg1, s32 *, 0);
        temp_a1 = M2C_FIELD(arg1, s32 *, 4);
        temp_a2 = M2C_FIELD(arg1, s32 *, 8);
        temp_a3 = M2C_FIELD(arg1, s32 *, 0xC);
        M2C_FIELD(temp_v1_3, s32 *, 0) = temp_a0;
        M2C_FIELD(temp_v1_3, s32 *, 4) = temp_a1;
        M2C_FIELD(temp_v1_3, s32 *, 8) = temp_a2;
        M2C_FIELD(temp_v1_3, s32 *, 0xC) = temp_a3;
        temp_a0 = M2C_FIELD(arg1, s32 *, 0x10);
        temp_a1 = M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(temp_v1_3, s32 *, 0x10) = temp_a0;
        M2C_FIELD(temp_v1_3, s32 *, 0x14) = temp_a1;
        return func_800244D4(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}
