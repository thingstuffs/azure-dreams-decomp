#include "common.h"

typedef s32 M2C_UNK;

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern M2C_UNK func_80047784();
extern M2C_UNK func_8009C93C();
extern s32 func_800A2B5C();
extern M2C_UNK func_800C7930();
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80175258[];

void func_80172514(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    FIELD(arg3, u8, 0x71) &= 0x7F;

    if (!(D_80083462 & 0x2000) &&
        ((func_800A2B5C(arg3) << 16) == 0) &&
        (func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300),
         ((func_800A2B5C(arg3) << 16) == 0))) {
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg0, u8, 0x9B) = 0;

        if (FIELD(arg0, u16, 0x98) & 0x8000) {
            FIELD(arg0, u8, 0x9A) = 0x17;
            FIELD(arg3, u8, 0x84) = 0x28;
            FIELD(arg3, u8, 0x85) = 0x10;
        } else {
            FIELD(arg0, u8, 0x9A) = 0x11;
            FIELD(arg3, u8, 0x84) = 0x7C;
            FIELD(arg3, u8, 0x85) = 0;
        }

        FIELD(arg2, void *, 0x2C) = D_80175258;
        func_80047784(
            arg2,
            D_80175258[((s32)(D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg3, u8, 0x6D)--;
        func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
    }
}
