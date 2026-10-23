#include "common.h"

extern void initialize_item_menu_request_state();
extern void initialize_item_menu_linked_blocks();
extern void initialize_item_menu_object_slots();
/*
 * Initializes the menu request, binds three embedded blocks at offsets 0x98/0x70/0x80, and
 * initializes its object slots.
 */
void initialize_item_menu_state(u8 *owner) {
    initialize_item_menu_request_state(owner);
    initialize_item_menu_linked_blocks(owner + 0x98, owner + 0x70, owner + 0x80);
    initialize_item_menu_object_slots(owner);
}
