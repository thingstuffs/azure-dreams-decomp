#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/item_menu.h"
#include "engine/graphics.h"

/* Global 32-bit flags word D_800814A0 (same global touched by the
 * func_8004B530 / set_object_cleanup_flag / set_object_and_global_removal_flag family, see code9.c). Here
 * retail reuses a single lui-based base register for both the load and the
 * store, so declare it as a >8B struct to force gcc to materialize one
 * shared %hi/%lo address instead of the two-independent-lui -G0 shape. */
extern s32 func_800B0198(ItemMenuObject *object, s32 entry_count);
extern ItemMenuPart *link_item_menu_object_entries(ItemMenuPart **parts);
extern void initialize_item_menu_state(ItemMenuObject *object, ItemMenuStateNode *owner);
extern void register_node(void *a0, void *a1);
/* Same callback registered by func_80050EF8 via register_node in this
 * overlay -- a real code symbol, not the data global m2c guessed. */
extern void release_null_terminated_entries(u16 **a0);

/* Allocate and initialize an object, register its callback, and flag initialization failure. */
ItemMenuObjectNode *create_item_menu_child_object(ItemMenuStateNode *owner)
{
    ItemMenuObjectNode *object;
    ItemMenuObject *menu;

    object = allocate_flagged_object_node(0);
    menu = &object->menu;
    if (object != 0) {
        if (func_800B0198(menu, 0x28) != 0) {
            object->header.sprite = (struct SpriteFrameState *)&object->menu.links;
            menu->chain = link_item_menu_object_entries(menu->parts);
            initialize_item_menu_state(menu, owner);
            register_node(object, (void *)draw_tinted_node_sprites_scratch);
            return object;
        }
        release_null_terminated_entries(object->menu.allocations);
        object->header.flags |= 0x8000;
        object = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return object;
}

