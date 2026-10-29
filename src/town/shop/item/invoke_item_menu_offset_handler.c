#include "common.h"
#include "m2c_compat.h"

#include "town/shop.h"
#include "town/shop/item.h"

/* Dispatch the menu state callback with the object payload and supplied argument. */
void invoke_item_menu_offset_handler(u8 *object, s32 callback_arg) {
    dispatch_item_menu_entry_callback(object + 0x20, callback_arg);
}
