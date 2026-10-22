#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"

/* Global 32-bit flags word D_800814A0 (same global touched by the
 * func_8004B530 / set_object_cleanup_flag / set_object_and_global_removal_flag family, see code9.c). Here
 * retail reuses a single lui-based base register for both the load and the
 * store, so declare it as a >8B struct to force gcc to materialize one
 * shared %hi/%lo address instead of the two-independent-lui -G0 shape. */
extern s32 func_800B0198(void *a0, s32 a1);
extern s32 link_item_menu_object_entries(s32 a0);
extern s32 initialize_item_menu_state(void *a0, s32 a1);
extern void register_node(void *a0, void *a1);
/* Same callback registered by func_80050EF8 via register_node in this
 * overlay -- a real code symbol, not the data global m2c guessed. */
extern int draw_tinted_node_sprites_scratch(void *a0, int a1, void *a2);
extern void release_null_terminated_entries(u16 **a0);

/* Allocate and initialize an object, register its callback, and flag initialization failure. */
void *create_item_menu_child_object(s32 init_value)
{
    void *object;
    void *object_data;

    object = allocate_flagged_object_node(0);
    object_data = (void *)((u8 *)object + 0x20);
    if (object != 0) {
        if (func_800B0198(object_data, 0x28) != 0) {
            *(void **)((u8 *)object + 0xC) = (u8 *)object + 0xB8;
            *(s32 *)((u8 *)object_data + 0xA4) = link_item_menu_object_entries(*(s32 *)((u8 *)object_data + 0xA8));
            initialize_item_menu_state(object_data, init_value);
            register_node(object, (void *)draw_tinted_node_sprites_scratch);
            return object;
        }
        release_null_terminated_entries((u16 **)((u8 *)object + 0xCC));
        *(u16 *)((u8 *)object + 0x1E) |= 0x8000;
        object = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return object;
}

