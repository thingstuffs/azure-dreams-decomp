#include "common.h"

#include "common.h"

extern void func_80035D4C(s16 arg0);
extern s32 func_80033B2C(s32 arg0);

extern s32 D_8006A944[];
extern s32 D_8006A948[];
extern s32 D_8006AC5C[];
extern s32 D_80080A50[];

/* Updates the selected entry and returns its value, applying special-case lookups. */
s32 func_80035DBC(s32 entry_index) {
    func_80035D4C((s16)entry_index);

    if (entry_index == 1) {
        return D_8006A944[0];
    }

    if (entry_index == 2) {
        return D_8006A948[0];
    }

    if (entry_index == 10 && func_80033B2C(0x1473) == 0) {
        return D_80080A50[0];
    }

    return D_8006AC5C[entry_index];
}
