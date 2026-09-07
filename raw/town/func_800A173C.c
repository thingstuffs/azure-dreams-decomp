#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800644B8();
M2C_UNK func_8009EF64();
M2C_UNK func_8009F1C0();
M2C_UNK func_8009F48C();
extern s32 D_800834B8[3];
extern M2C_UNK D_80093328;
extern M2C_UNK D_80093524[3];
extern s32 D_800CFCC4[3];

void func_8009EE9C(void *arg0, s32 arg1, void *arg2, M2C_UNK arg3) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg2, s32 *, 8);
    M2C_FIELD(arg2, s32 *, 8) = (u32) (M2C_FIELD(arg0, s32 *, 0xA0) + (func_800644B8(M2C_FIELD(arg0, s16 *, 0x6C)) << 6) + 0xFFFC0000);
    M2C_FIELD(arg0, s16 *, 0x6C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x6C) + 0x40);
    M2C_FIELD(arg2, s32 *, 0x14) = (s32) (M2C_FIELD(arg2, s32 *, 8) - temp_s0);
    if (D_800CFCC4[0] == arg1) {
        if (D_800834B8[0] == &D_80093328) {
            func_8009F1C0(arg0, D_800CFCC4[0], arg2, arg3);
            func_8009EF64();
            return;
        }
        if (D_800834B8[0] == D_80093524) {
            func_8009F48C(arg0, D_800CFCC4[0], arg2, arg3);
        }
    }
}
