#include "common.h"
#include "m2c_compat.h"

#include "town/shop.h"
#include "town/shop/item.h"

/* Dispatch the menu state callback with the object payload and supplied argument; returns the callback's result. */
s32 invoke_item_menu_offset_handler(u8 *object, s32 callback_arg) {
    return dispatch_item_menu_entry_callback(object + 0x20, callback_arg);
}
