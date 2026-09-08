#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800491F4();          /* extern */
extern M2C_UNK D_80027FC4;

/* Forwards the value to func_800491F4 with D_80027FC4 and 10. */
void func_80023ECC(M2C_UNK value) {
    func_800491F4(value, &D_80027FC4, 0xa);
}
