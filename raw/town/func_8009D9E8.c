#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033D08();
M2C_UNK func_8008F134();
s32 func_80096FF4();
M2C_UNK func_800970AC();
M2C_UNK func_8009B1FC();
s32 func_8009CFE0();
extern s32 D_800814A0[];

void func_8009B148(void *arg0, M2C_UNK arg1, M2C_UNK arg2)
{
    register M2C_UNK held_arg1 ASM_REG("$17") = arg1;
    register M2C_UNK held_arg2 ASM_REG("$18") = arg2;
    s8 *temp_v0;

    if (func_8009CFE0() != 0) {
        func_8008F134(arg0);
        temp_v0 = M2C_FIELD(arg0, s8 **, 0x98);
        if (temp_v0 != 0) {
            *temp_v0 = 0;
        }
        func_80033D08(arg0);
        M2C_FIELD(arg0, u16 *, -2) =
            (u16)(M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        func_8009B1FC();
        return;
    }
    M2C_FIELD(arg0, M2C_UNK (**)(void *, void *, M2C_UNK, M2C_UNK), 0x50)(
        arg0, arg0, held_arg1, held_arg2);
    if (!(M2C_FIELD(arg0, u16 *, -2) & 0x8000)) {
        func_800970AC(func_80096FF4(held_arg1), arg0);
    }
}
