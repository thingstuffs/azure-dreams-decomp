#include "common.h"
#include "m2c_compat.h"

void dispatch_item_menu_entry_callback();                         /* extern */

/* Calls dispatch_item_menu_entry_callback with the offset increased by 0x20. */
void invoke_item_menu_offset_handler(s32 offset) {
    dispatch_item_menu_entry_callback(offset + 0x20);
}
