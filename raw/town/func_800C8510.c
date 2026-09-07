#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);
extern void func_800C4174(void *arg0, M2C_UNK arg1, void *arg2);
extern u8 D_80082660;
extern M2C_UNK D_800D5518;
extern M2C_UNK D_800D5624;
extern M2C_UNK D_800D562C;
extern M2C_UNK D_800D5654;
extern M2C_UNK D_800D5658;

void func_800C5C70(void *arg0, M2C_UNK arg1, void *arg2) {
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x6000) {
        func_800C2E84(arg0, arg2, &D_800D5518);
        *((M2C_FIELD(arg0, s32 *, 0x60) * 8) + &D_80082660) = 0;
        M2C_FIELD(arg0, M2C_UNK **, 0x58) = &D_800D5654;
        M2C_FIELD(arg0, M2C_UNK **, 0x5C) = &D_800D5658;
        M2C_FIELD(arg0, M2C_UNK **, 0x7C) = &D_800D5624;
        M2C_FIELD(arg0, M2C_UNK **, 0x80) = &D_800D562C;
        M2C_FIELD(arg0, s8 *, 0x70) = 1;
        M2C_FIELD(arg0, u8 *, 0x71) = (u8) (M2C_FIELD(arg0, u8 *, 0x71) | 1);
        func_800C4174(arg0, arg1, arg2);
    }
}
