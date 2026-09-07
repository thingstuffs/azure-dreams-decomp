#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800C4174(void *arg0, void *arg1, s32 arg2);
extern void func_800C51CC(void);

void func_800C5100(void *arg0, void *arg1, s32 arg2) {
    if (M2C_FIELD(arg1, s32 *, 8) == -0x08000000) {
        func_800C4174(arg0, arg1, arg2);
        func_800C51CC();
        return;
    }

    M2C_FIELD(arg1, s32 *, 0x10) += 0xFFFE0000;
    M2C_FIELD(arg1, s32 *, 0x14) -= 0x8000;
    M2C_FIELD(arg1, s32 *, 4) += M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(arg1, s32 *, 8) += M2C_FIELD(arg1, s32 *, 0x14);

    if (M2C_FIELD(arg1, s32 *, 0x10) <= (s32)0xFF000000) {
        M2C_FIELD(arg1, s32 *, 0x10) = -0x01000000;
    }
    if (M2C_FIELD(arg1, s32 *, 0x14) <= (s32)0xFF000000) {
        M2C_FIELD(arg1, s32 *, 0x14) = -0x01000000;
    }
    if (M2C_FIELD(arg1, s32 *, 4) <= (s32)0xF8000000) {
        M2C_FIELD(arg1, s32 *, 4) = -0x08000000;
    }
    if (M2C_FIELD(arg1, s32 *, 8) <= (s32)0xF8000000) {
        M2C_FIELD(arg1, s32 *, 8) = -0x08000000;
    }
}
