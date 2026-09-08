#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018824();          /* extern */
extern M2C_UNK D_8001B218;

/* Passes D_8001B218 to func_80018824 with parameter 0x100. */
void func_80471380(void) {
    func_80018824(&D_8001B218, 0x100);
}
