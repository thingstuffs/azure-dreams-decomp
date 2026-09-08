#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800172A4();                         /* extern */
s32 func_80017BBC();                /* extern */

/* Pass the result of func_80017BBC(0xD, 2) to func_800172A4. */
void func_8059E6A4(void) {
    func_800172A4(func_80017BBC(0xD, 2));
}
