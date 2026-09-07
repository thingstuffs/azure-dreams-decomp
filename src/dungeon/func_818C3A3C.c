#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80025370() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern void func_8004491C();
extern s32 func_80069EF8();

extern u8 D_80025098[9];
extern u8 D_80025AF0[9];
extern u8 D_80045C34[9];

s32 func_818C3A3C(void *arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_lo;
    s32 temp_v1;
    s32 var_v0;
    register s32 result ASM_REG("$2");
    void *temp_s0;
    void *temp_s2;
    void *temp_v0;
    void *temp_v1_ptr;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s2 = (u8 *)temp_v0 + 0x20;
        FIELD(temp_v0, void *, 0x10) = D_80025098;
        FIELD(temp_v0, void *, 0x20) = arg0;
        FIELD(temp_s2, s16, 0x10) = 0;
        FIELD(temp_s2, u16, 0x14) = FIELD(arg0, u16, 0x14);

        temp_s0 = FIELD(temp_v0, void *, 0xC);
        FIELD(temp_s0, u8, 0xE) = 0x80;
        FIELD(temp_s0, u8, 0xD) = 0x80;
        FIELD(temp_s0, u8, 0xC) = 0x80;
        FIELD(temp_s0, s16, 0x12) = 0x7DCF;
        FIELD(temp_s0, u16, 0x14) |= 0xC;
        FIELD(temp_s0, u16, 0x10) |= 0x20;
        FIELD(temp_s0, u16, 0x14) |= 0x100;
        func_8003DB94(temp_s0, D_80025AF0, 0);

        var_v0 = func_80069EF8();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        FIELD(temp_s0, s16, 0x1A) = temp_v1 - ((var_v0 >> 12) << 12);

        temp_lo = 0x1400 / FIELD(temp_s2, s16, 0x14);
        FIELD(temp_s0, s16, 0x1E) = temp_lo;
        FIELD(temp_s0, s16, 0x1C) = temp_lo;
        func_8004491C(temp_v0, D_80045C34);

        temp_v1_ptr = FIELD(temp_v0, void *, 8);
        ASM_KEEP(temp_v1_ptr);
        result = (u32)temp_v0;
        ASM_KEEP(result);
        temp_a0 = FIELD(arg1, s32, 0);
        temp_a1 = FIELD(arg1, s32, 4);
        temp_a2 = FIELD(arg1, s32, 8);
        temp_a3 = FIELD(arg1, s32, 0xC);
        FIELD(temp_v1_ptr, s32, 0) = temp_a0;
        FIELD(temp_v1_ptr, s32, 4) = temp_a1;
        FIELD(temp_v1_ptr, s32, 8) = temp_a2;
        FIELD(temp_v1_ptr, s32, 0xC) = temp_a3;
        temp_a0 = FIELD(arg1, s32, 0x10);
        temp_a1 = FIELD(arg1, s32, 0x14);
        FIELD(temp_v1_ptr, s32, 0x10) = temp_a0;
        FIELD(temp_v1_ptr, s32, 0x14) = temp_a1;
        func_80025370(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}
