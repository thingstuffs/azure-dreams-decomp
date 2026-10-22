/* Item menu display lifecycle (G00607). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B2F64. */
#include "town/shop/item_menu_display_lifecycle_g00607.h"
#include "shared/object_node.h"

/* Create a display controller and its child display object. */
void *create_item_menu_display_controller(s32 owner, s32 display_config, s32 x, s32 y, s32 init_config) {
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
            object->unk_10 = &D_800B0490;
            display_object = create_item_menu_child_at_position(object, x, y, display_config, state->init_result, state);
            state->child = display_object;
            if (display_object == 0) {
                finish_item_menu_child_and_release_list(state);
                object = NULL;
            }
        }
    }
    return object;
}

/* Set the record and global high flags, then process the stored record value. */
void finish_item_menu_child_and_release_list(void *record) {
    s32 record_value;
    s32 global_flags;

    ((ObjectRetirementFlags *)record)[-1].unk_00 = (u16) (((ObjectRetirementFlags *)record)[-1].unk_00 | 0x8000);
    global_flags = D_800814A0.v | 0x8000;
    record_value = ((S_800B06C4_0 *)record)->child;
    D_800814A0.v = global_flags;
    release_item_menu_list_object(record_value);
}
