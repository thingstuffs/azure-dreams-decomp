#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017724();                     /* extern */
M2C_UNK func_8001779C();                     /* extern */

/* Apply five operations through func_8001779C, then process 0x9E1. */
void func_80761C28(void) {
    func_8001779C(0x12C1);
    func_8001779C(0x12C0);
    func_8001779C(0x9DA);
    func_8001779C(0x9DB);
    func_8001779C(0x9DC);
    func_80017724(0x9E1);
}
