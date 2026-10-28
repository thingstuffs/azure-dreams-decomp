#include "common.h"
#include "town/shop/storage_menu.h"                         /* extern */

/* Calls func_800B4B7C with the offset advanced by 0x20. */
void forward_offset_to_effect_finalizer(void *offset) {
    update_storage_display(offset + 0x20);
}
