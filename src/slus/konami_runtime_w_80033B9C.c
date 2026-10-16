#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void setResidentBitmapBit();                         /* extern */

/* Forwards a signed 16-bit value to setResidentBitmapBit. */
void func_80033B9C(s16 value) {
    setResidentBitmapBit(value);
}
