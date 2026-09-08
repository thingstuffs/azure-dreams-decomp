#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80027AFC();                /* extern */
M2C_UNK func_80027C60();                            /* extern */

/* Run setup and dispatch the request in mode 1. */
void func_80027D0C(s32 request) {
    func_80027C60();
    func_80027AFC(request, 1);
}
