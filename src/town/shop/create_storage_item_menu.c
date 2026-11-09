#include "town/shop/storage_menu.h"
#include "shared/object_flags.h"
#include "engine/item.h"
#include "engine/node.h"
#include "engine/resource.h"
#include "engine/text.h"
#include "engine/texture.h"
#include "engine/util.h"
#include "slus.h"
#include "town.h"
#include "town/person.h"
#include "town/shop/object.h"
#include "town/shop/state.h"
#include "town/shop.h"
extern int dungeon_menu_tag(void *forwarded_ptr, int unused_arg, void *second_ptr);

StorageMenuNode *create_storage_item_menu(ItemMenuStateNode *owner) {
    StorageMenuNode *object;
    StorageMenuObject *menu;
    object = allocate_flagged_object_node(0);
    menu = &object->menu;
    if (object != 0) {
        if (func_800B44F0(menu, 33) != 0) {
            object->header.sprite = &object->menu.links;
            menu->chain = process_target_with_code_33(menu->parts);
            func_800B44B0(menu, owner);
            register_node(object, dungeon_menu_tag);
            return object;
        }
        release_null_terminated_entries(object->menu.allocations);
        object->header.flags |= 0x8000;
        object = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return object;
}
