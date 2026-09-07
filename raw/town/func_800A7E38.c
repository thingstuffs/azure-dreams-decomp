#include "common.h"

extern s32 D_800834B8;
extern void func_800A553C(void *arg0, s32 arg1, s32 arg2);

void func_800A5598(void) {
    s32 *p = &D_800834B8;
    s32 *v = p - 8;

    
    func_800A553C(p, v[2], v[3]);
}
