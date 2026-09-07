#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80041094(); /* extern */
extern u16 D_80082E76;

void func_800B9430(void) {
    func_80041094(0x16, 0, 0, 0, D_80082E76 ^ 1);
}
