#include "common.h"
#include "m2c_compat.h"

#include "common.h"

s32 func_80033B2C();                         /* extern */

// Forwards a signed 16-bit value to func_80033B2C.
void func_80033BC0(s16 value) {
    func_80033B2C(value);
}
