#include "common.h"
#include "m2c_compat.h"

#include "common.h"

s32 testResidentBitmapBit();                         /* extern */

// Forwards a signed 16-bit value to testResidentBitmapBit.
void func_80033BC0(s16 value) {
    testResidentBitmapBit(value);
}
