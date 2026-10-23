#include "common.h"
#include "shared/object_links.h"
#include "frontend/card.h"

s32 func_80047938(void *, s32, s32);
void update_linked_object_value_and_flags();                      /* extern */

/* Run the object update and invoke its follow-up when flag 0x2000 is set. */
void update_object_and_flag_linked(void *object_data, s32 first_value, s32 second_value) {
    u16 object_flags;
    func_80047938(object_data, first_value, second_value);
    object_flags = ((ObjectStatusPrefix16 *)((u8 *)object_data - 0x2))->flags;
    object_data = (s8 *) object_data - 0x20;
    if (object_flags & 0x2000) {
        update_linked_object_value_and_flags(object_data);
    }
}
