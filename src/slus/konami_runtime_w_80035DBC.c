#include "common.h"

#include "common.h"

extern void func_80035D4C(s16 arg0);
extern s32 func_80033B2C(s32 arg0);

extern s32 D_8006A944[];
extern s32 D_8006A948[];
extern s32 D_8006AC5C[];
extern s32 D_80080A50[];

s32 func_80035DBC(s32 arg0) {
    func_80035D4C((s16)arg0);

    if (arg0 == 1) {
        return D_8006A944[0];
    }

    if (arg0 == 2) {
        return D_8006A948[0];
    }

    if (arg0 == 10 && func_80033B2C(0x1473) == 0) {
        return D_80080A50[0];
    }

    return D_8006AC5C[arg0];
}
