#include "common.h"
#include "m2c_compat.h"

s32 find_resource_index_by_key(s32, M2C_UNK, M2C_UNK);                                /* extern */
void move_resource_to_front();                         /* extern */
s32 install_resource_descriptor_at_front();      /* extern */

/* Find or allocate the matching entry and move it to the front. */
void ensure_resource_at_front(s32 kind, M2C_UNK state, M2C_UNK value) {
    s32 entry_index;

    entry_index = find_resource_index_by_key(kind, state, value);
    if (entry_index < 0) {
        entry_index = install_resource_descriptor_at_front(kind, state, value, entry_index & 0x7FFFFFFF);
    }
    if (entry_index != 0) {
        move_resource_to_front(entry_index);
    }
}
