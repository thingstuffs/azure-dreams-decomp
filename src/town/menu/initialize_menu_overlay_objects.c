#include "frontend/card/slot_details.h"
#include "common.h"
#include "town/scene.h"
#include "town/menu.h"

/*
 * Stores the owning node, binds three embedded primitive blocks at offsets
 * 0xAF8/0xAD0/0xAE0, and initializes menu item positions.
 */
void initialize_menu_overlay_objects(CardDevSlotDetails *panel, ObjectNodeHeader *owner) {
    write_value_through_pointer(panel, owner);
    initialize_menu_primitive_settings(&panel->template_node, &panel->primary, &panel->secondary);
    initialize_menu_item_positions(panel);
}
