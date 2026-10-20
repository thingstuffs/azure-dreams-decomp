#include "common.h"

void release_object_and_compact_slot_list(s32 slotIndex);
s32 func_80017BBC();                /* extern */

/* Pass the result of func_80017BBC(0xD, 2) to release_object_and_compact_slot_list. */
void release_object_slot_d_2(void) {
    release_object_and_compact_slot_list(func_80017BBC(0xD, 2));
}
