#include "common.h"
#include "shared/item_menu.h"

extern void initialize_item_menu_request_state(ItemMenuObject *object, ItemMenuStateNode *owner);
extern void initialize_item_menu_linked_blocks(ItemMenuDisplayLinks *links, ItemMenuDisplayBlock *display,
                                               DisplayPositionWords *position);
extern void initialize_item_menu_object_slots(ItemMenuObject *object);
/*
 * Initializes the menu request for the owning menu node, binds the display link block to the display
 * block and display position, and initializes the object's part slots.
 */
void initialize_item_menu_state(ItemMenuObject *object, ItemMenuStateNode *owner) {
    initialize_item_menu_request_state(object, owner);
    initialize_item_menu_linked_blocks(&object->links, &object->display, &object->display_position);
    initialize_item_menu_object_slots(object);
}
