#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_800A2B04();
extern M2C_UNK func_800A56E0();
extern void func_80173594(void) __attribute__((noreturn));
extern s32 D_8008346C;
extern M2C_UNK D_80170E94;

void func_8017346C(void *arg0, void *arg1, void *arg2, void *arg3) {
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            func_80173594();
            return;
        }
        goto block_8;
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(arg0, u8 *, 0x9B) = 1U;
        M2C_FIELD(arg2, u16 *, 0x14) |= 0x6000;
        func_80173594();
        return;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_8:
    if (((M2C_FIELD(arg2, s8 *, 4) == 5) && (M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) || (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        func_800A56E0(0x803);
    }
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
        M2C_FIELD(arg0, s8 *, 0xAE) = 1;
        M2C_FIELD(arg3, s32 *, 0x14) = (s32) (M2C_FIELD(arg3, s32 *, 0x14) | 0x40000000);
        M2C_FIELD(arg1, s32 *, 0x14) = 0;
        M2C_FIELD(arg1, s32 *, 0x10) = 0;
        M2C_FIELD(arg1, s32 *, 0xC) = 0;
        func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
        M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80170E94;
        D_8008346C = 0;
    }
}
