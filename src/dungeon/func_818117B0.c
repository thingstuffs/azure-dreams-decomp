#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800491F4(M2C_UNK, void *, s32);          /* extern */
extern M2C_UNK D_80029500;

/* Forwards the value to func_800491F4 with D_80029500 and constant 4. */
void func_800267B0(M2C_UNK value) {
    func_800491F4(value, &D_80029500, 4);
}
