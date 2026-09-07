#include "common.h"

/* OR-accumulates flag bits from D_80073740[0..D_80073734[0]-1], then calls func_8005E97C(0, accumulated_flags). */
extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern void func_8005E97C(s32 arg0, s32 arg1);

void func_8005B418(void) {
    s32 mask;
    s32 i;

    mask = 0;
    for (i = 0; i < D_80073734[0]; i++) {
        mask |= D_80073740[i];
    }
    func_8005E97C(0, mask);
}
