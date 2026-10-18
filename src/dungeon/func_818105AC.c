#include "common.h"
#include "m2c_compat.h"

void inventory_set_embedded_state_four();                         /* extern */

typedef struct S_800255AC_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_800255AC_0;   /* arg0 in forward_stored_object_value */

/* Passes the object's stored value to inventory_set_embedded_state_four. */
void forward_stored_object_value(S_800255AC_0 *object) {
    inventory_set_embedded_state_four(object->unk_40);
}
