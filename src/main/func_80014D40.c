#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80027AFC();                /* extern */
M2C_UNK func_80027C60();                            /* extern */
M2C_UNK func_800A68C0();                            /* extern */

/* Run the extra setup callback and dispatch the request in mode 2. */
void func_80027D40(s32 request) {
    func_800A68C0();
    func_80027C60();
    func_80027AFC(request, 2);
}
