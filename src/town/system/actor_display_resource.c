/* Actor display resource and its file-private helper. */
#include "common.h"
#include "shared/item_menu.h"
extern void *realloc_field_0_buffer(void *buffer_slot, s32 entry_count, s32 clear_words);
extern void texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(ItemMenuPart **entries, DisplayPositionWords *value, s32 count);
extern s32 display_vector_defaults[];
#include "shared/object_node.h"
#include "shared/object_flags.h"
/* Global 32-bit flags word D_800814A0 (same global touched by the
 * func_8004B530 / set_object_cleanup_flag / set_object_and_global_removal_flag family, see code9.c). Here
 * retail reuses a single lui-based base register for both the load and the
 * store, so declare it as a >8B struct to force gcc to materialize one
 * shared %hi/%lo address instead of the two-independent-lui -G0 shape. */
extern s32 func_800B0198(ItemMenuObject *object, s32 entry_count);
extern ItemMenuPart *link_item_menu_object_entries(ItemMenuPart **parts);
extern void initialize_item_menu_state(ItemMenuObject *object, ItemMenuStateNode *owner);
extern void register_node(void *a0, void *a1);
extern void func_8004491C(void *a0, void *a1);
/* Same callback registered by func_80050EF8 via func_8004491C in this
 * overlay -- a real code symbol, not the data global m2c guessed. */
extern int draw_tinted_node_sprites_scratch(void *a0, int a1, void *a2);
extern int func_8004CAA0(void *a0, int a1, void *a2);
extern void release_null_terminated_entries(u16 **a0);
extern void func_8004B248(u16 **a0);

/* Allocates actor display entries, shares a default vector across 40 entries, and reports success. */
static s32 load_actor_display_resource(ItemMenuObject *object, s32 entry_count) {
    s32 success = 0;
    ItemMenuPart **parts = realloc_field_0_buffer(object->allocations, entry_count, 12);

    object->parts = parts;
    if (parts != 0) {
        object->part_vector.unk0 = display_vector_defaults[0];
        object->part_vector.unk4 = display_vector_defaults[1];
        object->part_vector.unk8 = display_vector_defaults[2];
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(parts, &object->part_vector, 40);
        success = 1;
    }
    return success;
}

/* Allocates and initializes an item menu object, releasing its entries if display setup fails. */
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
