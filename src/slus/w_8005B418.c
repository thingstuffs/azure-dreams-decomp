#include "common.h"

extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern void func_8005E97C(s32 arg0, s32 arg1);

/* Combines flags from D_80073740 and passes them to func_8005E97C. */
void func_8005B418(void) {
    s32 flags;
    s32 flag_index;

    flags = 0;
    for (flag_index = 0; flag_index < D_80073734[0]; flag_index++) {
        flags |= D_80073740[flag_index];
    }
    func_8005E97C(0, flags);
}
