#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80098B38();
M2C_UNK func_800990C8();
s32 func_8009C12C();
M2C_UNK func_8009C93C();
extern u16 D_80083460[];
extern s32 D_800E3D7C;

s32 func_80098864(s32 arg0, void *arg1) {
    s32 temp_s0;
    void *temp_a0;

    D_80083460[5]--;
    temp_s0 = M2C_FIELD(arg1, s32 *, -0x14);
    func_800990C8(arg1, arg0);
    func_8009C93C(arg1, temp_s0, M2C_FIELD(arg1, s16 *, 0x2A), 0, 0);
    if (func_8009C12C(arg1, temp_s0, M2C_FIELD(arg1, s16 *, 0x2A), 0) == 0) {
        return 0;
    }
    temp_a0 = M2C_FIELD(arg1, void **, 0x60);
    if (temp_a0 != 0) {
        M2C_FIELD(temp_a0, s32 *, 0x60) = (s32) D_800E3D7C;
    }
    func_80098B38(arg0);
    return 1;
}
