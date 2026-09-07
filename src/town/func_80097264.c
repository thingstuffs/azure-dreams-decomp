#include "common.h"

void func_80048A44();
s32 func_80095360();
extern u8 D_80080A84;

void func_800949C4(u8 *arg0, s32 arg1, u8 *arg2) {
    s32 offset;

    offset = func_80095360(arg1);
    func_80048A44(arg2, *(arg0 + offset), 0, 0);
    arg2[5] = arg2[5] + (2 / (s32)D_80080A84);
}

/* MECHANISM: The two cross-call pointer lifetimes are explicit: arg0 becomes the
   byte base used by the nested second-call argument, while arg2 stays held.
   Byte typing removes scaling; nested argument form orders a0 setup before addu. */
