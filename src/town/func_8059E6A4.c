#include "common.h"
#include "m2c_compat.h"

M2C_UNK release_object_and_compact_slot_list();                         /* extern */
s32 func_80017BBC();                /* extern */

/* Pass the result of func_80017BBC(0xD, 2) to release_object_and_compact_slot_list. */
void func_8059E6A4(void) {
    release_object_and_compact_slot_list(func_80017BBC(0xD, 2));
}
