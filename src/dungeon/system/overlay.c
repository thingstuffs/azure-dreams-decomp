#include "common.h"

extern s32 allocate_item_object(s32, s32, s32, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Forwards the item request with no data override. */
void allocate_item_without_data_override(s32 owner, s32 context, s32 mode, s32 item_id) {
    allocate_item_object(owner, context, mode, item_id, 0);
}
