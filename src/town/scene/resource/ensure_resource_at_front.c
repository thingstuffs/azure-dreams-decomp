#include "common.h"
s32 find_resource_index_by_key(s32 targetField0, s32 targetField1, s32 targetField2);                                /* extern */
void move_resource_to_front(s32);                         /* extern */
s32 install_resource_descriptor_at_front(s32, s32, s32, s32);      /* extern */

/* Find or allocate the matching entry and move it to the front. */
void ensure_resource_at_front(s32 kind, s32 state, s32 value) {
    s32 entry_index;

    entry_index = find_resource_index_by_key(kind, state, value);
    if (entry_index < 0) {
        entry_index = install_resource_descriptor_at_front(kind, state, value, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        move_resource_to_front(entry_index);
    }
}
