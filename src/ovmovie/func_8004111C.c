#include "common.h"
#include "m2c_compat.h"

s32 func_80177948();                                /* extern */
M2C_UNK func_80177C58();                            /* extern */
u32 func_80177CF0();                                /* extern */

s32 func_8004111C(s32 arg0) {
    if (arg0 != 0) {
        return (func_80177CF0() >> 0x18) & 1;
    }
    func_80177C58();
    return func_80177948();
}
