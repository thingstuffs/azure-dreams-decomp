#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80702670();                     /* extern */

/* Calls func_80702670 with 0x20C and returns the value at 0x80701FBC. */
s32 func_807025E8(void) {
    func_80702670(0x20C);
    return *(s32 *)0x80701FBC;
}
