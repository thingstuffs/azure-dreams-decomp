#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80016904(void) __attribute__((noreturn));
extern s32 func_800176B8();
extern M2C_UNK func_800177CC();
extern M2C_UNK func_80018594();
extern s32 func_8001868C();
extern void *D_80016000[];

s32 func_80016844(void *arg0, M2C_UNK arg1) {
    s32 temp_v0;
    s32 var_v0;

    var_v0 = 0;
    if (func_8001868C(0x1459) != 0) {
        func_80018594(M2C_FIELD(arg0, s16 *, 0x18));
        M2C_FIELD(((M2C_FIELD(D_80016000[0], s32 *, 8) * 8) +
                   M2C_FIELD(D_80016000[0], s32 *, 0x40)),
                  s8 *, 4) = 0;
        func_800177CC(arg0, arg1);
        func_80016904();
    }
    if (func_8001868C(0x1458) != 0) {
        func_80018594(M2C_FIELD(arg0, s16 *, 0x18));
        var_v0 = func_800176B8(arg0, arg1);
        if (var_v0 != 0) {
            M2C_FIELD(((M2C_FIELD(D_80016000[0], s32 *, 8) * 8) +
                       M2C_FIELD(D_80016000[0], s32 *, 0x40)),
                      s8 *, 4) = 0;
        }
    }
    return var_v0;
}
