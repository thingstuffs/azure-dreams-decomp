#include "common.h"
#include "m2c_compat.h"
#include "town/shop/item_menu_actions.h"
#include "town/shop/item.h"
#include "shared/object_node.h"

/* Release the selected display, re-enable the primary menu and clear the owner's update. */
void release_item_menu_record_child(ItemMenuState *state) {
    schedule_item_menu_child_release(state->display_controller);
    state->display_controller = 0;
    set_item_menu_record_active(state->menu_object);
    NODE_HEADER(state)->update_callback = 0;
}
