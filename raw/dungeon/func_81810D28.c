#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void func_80025D28(void *arg0) {
    volatile s32 sp0;
    s32 value;
    u8 flags;

    sp0 = 0xB8C8;
    M2C_FIELD(arg0, s8 *, 1) = 0x28;
    value = sp0;
    flags = M2C_FIELD(arg0, u8 *, 0);
    M2C_FIELD(arg0, s8 *, 2) = 2;
    M2C_FIELD(arg0, s8 *, 3) = 2;
    M2C_FIELD(arg0, s8 *, 0xA) = 0xC;
    M2C_FIELD(arg0, s8 *, 0xB) = 0xC;
    M2C_FIELD(arg0, s32 *, 4) = value;
    M2C_FIELD(arg0, u8 *, 0) = (u8)(flags | 0x80);
}
