#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_800942B0();
extern M2C_UNK D_800903FC[];
extern M2C_UNK D_800970FC[];
extern s32 D_800D0CC0[];

void func_800A55CC(void *arg0, void *arg1) {
    s32 delta;

    M2C_FIELD(arg0, M2C_UNK **, -0x10) = D_800903FC;
    func_800942B0();
    {
        register void *call_arg0 ASM_REG("$4") = arg0;
        register void *call_arg1 ASM_REG("$5") = D_800970FC;

        ASM_KEEP(call_arg0);
        ASM_KEEP(call_arg1);
        delta = 0x10000;
        M2C_FIELD(arg1, s32 *, 8) =
            (M2C_FIELD(arg1, s32 *, 8) + delta) - D_800D0CC0[0];
        func_80033CD8(call_arg0, call_arg1, delta);
    }
}
