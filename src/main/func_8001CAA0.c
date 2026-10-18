#include "common.h"
#include "m2c_compat.h"
void func_80047358(s32, void *, s32);            /* extern */
extern M2C_UNK D_80408C9C;

/* Pass the caller's context and fixed data to func_80047358. */
void func_8001CAA0(s32 context) {
    func_80047358(context, &D_80408C9C, 0x12);
}
