#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800491F4();          /* extern */
extern M2C_UNK D_80027F60;

/* Forwards the input to func_800491F4 with &D_80027F60 and 7. */
void func_80022B20(M2C_UNK input) {
    func_800491F4(input, &D_80027F60, 7);
}
