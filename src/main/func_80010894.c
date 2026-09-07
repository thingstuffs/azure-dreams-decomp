#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80023600();                         /* extern */
M2C_UNK func_80023730();               /* extern */
M2C_UNK func_8002388C();                            /* extern */

void func_80023894(s32 arg0) {
    func_8002388C();
    func_80023730(arg0 + 0x190, arg0 + 0x168, arg0 + 0x178);
    func_80023600(arg0);
}
