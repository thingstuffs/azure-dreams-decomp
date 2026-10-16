#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void clearResidentBitmapBit();                         /* extern */

/* Forward a signed 16-bit value to clearResidentBitmapBit. */
void func_80033B78(s16 value) {
    clearResidentBitmapBit(value);
}
