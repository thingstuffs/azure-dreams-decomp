/* Item menu display lifecycle. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B2F64. */
#include "town/shop/item_menu_display_lifecycle_g00607.h"
#include "shared/object_node.h"
#include "town/shop.h"
#include "town/system_callbacks_api.h"

/* Create a display controller and its child display object. */
void *create_item_menu_display_controller(ItemMenuStateNode *owner, s32 display_config, s32 x, s32 y, void *init_config) {
    s32 init_result;
    s32 display_object;
    S_800B05DC_0 *state;
    ObjectNodeHeader *object;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        state->owner = owner;
        state->init_config = init_config;
        state->display_config = display_config;
        bzero(state, 4);
        init_result = set_item_menu_flag_and_return_one(state, init_config);
        state->init_result = init_result;
        if (init_result != 0) {
            object->update_callback = handle_item_menu_input;
            display_object = create_item_menu_child_at_position(object, x, y, display_config, state->init_result, state);
            state->child = display_object;
            if (display_object == 0) {
                release_item_menu_display(state);
                object = NULL;
            }
        }
    }
    return object;
}

/* Set the record and global high flags, then process the stored record value. */
void release_item_menu_display(void *record_arg) {
    ObjectRetirementFlags *record = record_arg;
    s32 record_value;
    s32 global_flags;

    record[-1].flags = (u16) (record[-1].flags | 0x8000);
    global_flags = object_flag_block.v | 0x8000;
    record_value = ((S_800B06C4_0 *)record)->child;
    object_flag_block.v = global_flags;
    release_item_menu_list_object(record_value);
}
