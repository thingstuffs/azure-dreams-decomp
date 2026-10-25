#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
struct S_8001FF0C_0;

void func_80406F0C(struct S_8001FF0C_0 *object, s32 value);                            /* extern */

/* Store a value in the object's field at offset 0x20. */
void card_dev_load_forward_object_value(void *object, s32 value) {
    func_80406F0C(object, value);
}
