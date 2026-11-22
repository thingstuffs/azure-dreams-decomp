#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
#include "engine/item.h"
#include "town.h"



/* Updates an object's state and sets its local and global 0x8000 flags. */
void release_item_menu_list_object(ObjectNodeHeader *object) {
    ItemMenuTransition *display;

    if (object != 0) {
        display = NODE_BODY(object);
        remove_item_menu_entry_objects(display->rows.as_ptr, display->entry_count);
        release_null_terminated_entries(display->allocations);
        NODE_HEADER(display)->flags |= 0x8000;
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
