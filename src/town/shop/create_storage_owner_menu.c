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
extern u8 shop_cursor_template[];
extern u8 D_80071244[];
extern void func_800B5020(void *work);
extern void forward_source_data_to_component(void *object);
extern void update_control_indicators_and_flags(void *object);
extern void forward_record_fields_to_page_loader(void *loader, void *object);
extern s32 display_block_defaults[4];
extern DisplayPositionWords display_vector_defaults;
extern int dungeon_menu_tag(void *forwarded_ptr, int unused_arg, void *second_ptr);
extern ItemMenuPart *func_800B4C94(ItemMenuPart **parts);

StorageMenuNode *create_storage_owner_menu(ItemMenuStateNode *owner) {
    StorageMenuNode *object;
    StorageMenuObject *menu;
    object = allocate_flagged_object_node(0);
    menu = &object->menu;
    if (object != 0) {
        if (func_800B4ED8(menu, 41) != 0) {
            object->header.sprite = &object->menu.links;
            menu->chain = func_800B4C94(menu->parts);
            initialize_four_slot_object_owner(menu, owner);
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
