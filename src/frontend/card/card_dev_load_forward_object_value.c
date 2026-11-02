#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
struct S_8001FF0C_0;


/* Store a value in the object's field at offset 0x20. */
void card_dev_load_forward_object_value(void *object, s32 value) {
    card_dev_load_set_object_value(object, value);
}
