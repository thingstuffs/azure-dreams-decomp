#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80020EA0();                            /* extern */
M2C_UNK func_8005863C();                            /* extern */
extern s8 D_80080A84;

/* Run setup callbacks and set the active flag. */
void func_80027C60(void) {
    func_8005863C();
    D_80080A84 = 1;
    func_80020EA0();
}
