#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800491F4();          /* extern */
extern M2C_UNK D_80027FF8;

/* Calls func_800491F4 for the target with fixed data and a value of 0x15. */
void func_80024C48(M2C_UNK target) {
    func_800491F4(target, &D_80027FF8, 0x15);
}
