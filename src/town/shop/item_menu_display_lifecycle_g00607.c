/* Item menu display lifecycle (G00607). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B2F64. */
#include "town/shop/item_menu_display_lifecycle_g00607.h"

/* Create a display controller and its child display object. */
void *create_item_menu_display_controller(s32 owner, s32 display_config, s32 x, s32 y, s32 init_config) {
    s32 init_result;
    s32 display_object;
    S_800B05DC_0 *state;
    void *object;

    object = func_8003FC64(0);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_08 = owner;
        state->unk_0C = init_config;
        state->unk_14 = display_config;
        bzero(state, 4);
        init_result = set_item_menu_flag_and_return_one(state, init_config);
        state->unk_18 = init_result;
        if (init_result != 0) {
            ((S_800B05DC_1 *)object)->unk_10 = &D_800B0490;
            display_object = create_item_menu_child_at_position(object, x, y, display_config, state->unk_18, state);
            state->unk_04 = display_object;
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
    record_value = ((S_800B06C4_0 *)record)->unk_04;
    D_800814A0.v = global_flags;
    release_item_menu_list_object(record_value);
}
