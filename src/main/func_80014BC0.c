#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8006A084();                            /* extern */
M2C_UNK func_8006A094();                            /* extern */
M2C_UNK func_8006A248();                     /* extern */

void func_80027BC0(void) {
    func_8006A084();
    func_8006A248(0xF2000002);
    func_8006A094();
}
