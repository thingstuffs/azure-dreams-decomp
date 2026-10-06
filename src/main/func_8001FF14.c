#include "common.h"
#include "m2c_compat.h"

void func_80406F0C();                            /* extern */

/* Store a value in the object's field at offset 0x20. */
void func_8001FF14(void *object, s32 value) {
    func_80406F0C(object, value);
}
