#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001E578();                     /* extern */
extern M2C_UNK D_80021F20;

/* Calls func_8001E578 with 0x400 and returns the address of D_80021F20. */
M2C_UNK *func_8001AC78(void) {
    func_8001E578(0x400);
    return &D_80021F20;
}
