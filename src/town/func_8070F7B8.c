#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001A5CC();                     /* extern */
extern M2C_UNK D_8001AFB8;
extern M2C_UNK *D_8001B170;

/* Calls func_8001A5CC with 0x118A and points D_8001B170 at D_8001AFB8. */
void func_8070F7B8(void) {
    func_8001A5CC(0x118A);
    D_8001B170 = &D_8001AFB8;
}
