#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800491F4();          /* extern */
extern M2C_UNK D_80027F68;

/* Forwards the input with fixed data D_80027F68 and parameter 0x12. */
void func_800237C4(M2C_UNK input) {
    func_800491F4(input, &D_80027F68, 0x12);
}
