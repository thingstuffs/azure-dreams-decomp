#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018BD0();                     /* extern */
s32 func_80018C50();                         /* extern */

s32 func_800165F8(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    return func_80018C50(0xFC0) != 0;
}
