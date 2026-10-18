#include "common.h"
#include "m2c_compat.h"

s32 func_80047358(s32, void *, s32);
extern M2C_UNK D_80408D28;

/* Forwards value to func_80047358 with D_80408D28 and constant 0x15. */
void func_8001E6CC(s32 value) {
    func_80047358(value, &D_80408D28, 0x15);
}
