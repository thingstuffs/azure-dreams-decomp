#include "common.h"
#include "m2c_compat.h"

s32 func_80047358(s32, void *, s32);
extern M2C_UNK D_80408D64;

/* Forward the context to func_80047358 with D_80408D64 and a fixed argument of 4. */
void func_800205A8(s32 context) {
    func_80047358(context, &D_80408D64, 4);
}
