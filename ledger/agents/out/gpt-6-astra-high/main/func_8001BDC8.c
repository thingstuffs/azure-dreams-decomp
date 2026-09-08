#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047358();            /* extern */
extern M2C_UNK D_80408C84;

/* Forwards the target with fixed data D_80408C84 and value 6. */
void func_8001BDC8(M2C_UNK target) {
    func_80047358(target, &D_80408C84, 6);
}
