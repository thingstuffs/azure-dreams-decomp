#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80041284();                   /* extern */
extern M2C_UNK D_800D1B64;

/* Pass D_800D1B64 to func_80041284. */
void func_800B9890(void) {
    func_80041284(&D_800D1B64);
}
