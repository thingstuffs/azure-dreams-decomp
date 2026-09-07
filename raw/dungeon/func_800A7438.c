#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern struct {
    s8 pad[0xA];
    u16 field_0xA;
} D_80083460;

void func_800ACB98(void *arg0, void *arg1, void *arg2, void *arg3) {
    M2C_FIELD(arg0, s8 *, 0x9A) = 0x14;
    M2C_FIELD(arg0, s8 *, 0x9B) = 0;
    M2C_FIELD(arg0, s32 *, 0x8C) = 0;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16)(M2C_FIELD(arg2, u16 *, 0x14) | 0x800);
    M2C_FIELD(arg0, s16 *, 0x96) = 0;
    D_80083460.field_0xA = D_80083460.field_0xA + 1;
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32)(M2C_FIELD(arg3, s32 *, 0x1C) | 0x10000000);
}
