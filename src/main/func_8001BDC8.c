#include "common.h"
#include "m2c_compat.h"
void func_80047358(s32, void *, s32);            /* extern */
extern M2C_UNK D_80408C84;

/* Forwards the target with fixed data D_80408C84 and value 6. */
void func_8001BDC8(s32 target) {
    func_80047358(target, &D_80408C84, 6);
}
