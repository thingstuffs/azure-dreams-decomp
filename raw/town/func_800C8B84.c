#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);
extern u8 D_80082660;
extern M2C_UNK D_800C3B7C;
extern M2C_UNK D_800D5670;

void func_800C62E4(void *arg0, s32 unused1, s32 arg2) {
    func_800C2E84(arg0, arg2, &D_800D5670);
    *((M2C_FIELD(arg0, s32 *, 0x60) * 8) + &D_80082660) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0x54) = &D_800C3B7C;
    M2C_FIELD(arg0, s16 *, 0x6C) = 0x20;
}
