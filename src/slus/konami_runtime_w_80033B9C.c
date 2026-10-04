#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void func_80033AA8();                         /* extern */

/* Forwards a signed 16-bit value to func_80033AA8. */
void func_80033B9C(s16 value) {
    func_80033AA8(value);
}
