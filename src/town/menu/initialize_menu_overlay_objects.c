#include "common.h"
#include "town/scene.h"
#include "town/menu.h"

extern void initialize_menu_primitive_settings(void *, void *, void *);
extern void initialize_menu_item_positions(void *);
/*
 * Stores the supplied owner value, binds three embedded primitive blocks at offsets
 * 0xAF8/0xAD0/0xAE0, and initializes menu item positions.
 */
void initialize_menu_overlay_objects(u8 *owner, s32 value) {
    write_value_through_pointer(owner, value);
    initialize_menu_primitive_settings(owner + 0xAF8, owner + 0xAD0, owner + 0xAE0);
    initialize_menu_item_positions(owner);
}
