#include "common.h"
#include "shared/object_flags.h"
#include "shared/item_menu.h"
#include "engine/item.h"
#include "town/shop/item.h"
#include "town/shop/state.h"

extern s32 D_800814A0;

// Process a non-null object and set its local and global 0x8000 flags.
void reset_item_menu_object_state(ItemMenuObjectNode *object)
{
    ItemMenuObject *menu;

    if (object != 0) {
        menu = &object->menu;
        release_null_terminated_entries(object->menu.allocations);
        clear_item_menu_entry_groups(menu->parts);
        object->header.flags |= 0x8000;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
