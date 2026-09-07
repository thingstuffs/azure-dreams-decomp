#include "common.h"

extern void func_800A510C(void);
extern s32 D_80100DE0[];

void func_800A5130(void) {
    s32 *base = &D_80100DE0[0];

    func_800A510C();
    
    *(s32 *)((s8 *)base + 4) = 0;
}
