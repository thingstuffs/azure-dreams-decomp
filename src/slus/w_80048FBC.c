#include "common.h"

extern s32 func_80048F8C(s32 *a0, s32 a1);
extern s32 func_8004B404(s32 a0);

/* Looks up the count/index returned by func_80048F8C(a0, a1), computes a
   value via func_8004B404(0x104), stores that value into the a0 array at
   the returned index, and returns the stored value. */
s32 func_80048FBC(s32 *a0, s32 a1)
{
    s32 idx = func_80048F8C(a0, a1);
    s32 v = func_8004B404(0x104);
    a0[idx] = v;
    return v;
}
