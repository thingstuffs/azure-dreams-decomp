#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80047784();
M2C_UNK func_8009C93C();
s32 func_800A0134();
s32 func_800A04F0();
s32 func_800A2B5C();
s32 func_800A2CB8();
M2C_UNK func_800C7930();

extern s16 D_80083228;
extern s32 D_80083460;
extern u16 D_80083462;
extern u8 D_800E2378;

s32 func_80172E80(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    s32 result;
    s32 state;
    s32 value;
    s32 flags;
    s32 *flags_base;
    u8 *table;

    M2C_FIELD(arg3, u8 *, 0x71) &= 0x7F;
    flags_base = &D_80083460;
    state = 0;
    if (M2C_FIELD(flags_base, u16 *, 2) & 0x2000) {
        goto return_minus_one;
    }

    value = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24),
                         M2C_FIELD(arg2, u8 *, 0x25),
                         M2C_FIELD(arg3, s16 *, 0x2A));
    result = 0;
    if ((func_800A2CB8(arg3, value) << 16) == 0) {
        goto return_zero;
    }

    result = -1;
    flags = M2C_FIELD(flags_base, u16 *, 2);
    if (flags & 0x2000) {
        return result;
    }
    if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
        if (flags & 8) {
            return result;
        }
    }

    if ((u16)((0 - func_800A0134(value, arg3)) + 0x40) >= 0x81U) {
        return state;
    }

    state = 1;
    if (!(M2C_FIELD(arg3, u16 *, 0x46) & 0x8000)) {
        if (D_80083462 & 8) {
            return -1;
        }
    }
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((s8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) != 0) {
return_minus_one:
        return -1;
    }

    result = state;
    M2C_FIELD(arg0, u8 *, 0x9B) = 0;
    if (result != 0) {
        M2C_FIELD(arg0, u8 *, 0x9A) = 0x11;
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg3, u8 *, 0x84) = 0x7C;
        M2C_FIELD(arg3, u8 *, 0x85) = 0;
        M2C_FIELD(arg0, u16 *, 0x98) &= 0xFFF7;
        M2C_FIELD(arg3, s32 *, 0x1C) &= 0xFFFBFFFF;
        table = &D_800E2378;
        M2C_FIELD(arg2, u8 **, 0x2C) = table;
        func_80047784(arg2,
                      table[((D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7],
                      0);
        M2C_FIELD(arg3, u8 *, 0x6D)--;
        func_8009C93C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1, 0);
    }
    return result;

return_zero:
    return 0;
}
