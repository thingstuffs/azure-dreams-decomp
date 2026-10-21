/* Initialize player effect handlers from prior state (G00576). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A7DDC. */
#include "town/player/effect_handlers_g00576.h"

/* Set the record handlers, initialize its data, clear the global state, and finish setup. */
void initialize_effect_record_handlers(void *record_data, s32 unused, s32 destination) {
    ((S_800A553C_0 *)((u8 *)record_data - 0x10))->unk_00 = &D_800A5638;
    store_the_in_forwards_field_10_callee_800949_c_4((s32) &D_800D0C50, record_data, (void *) destination);
    ((S_800A553C_0 *)((u8 *)record_data - 0x10))->unk_10 = &update_town_movement_and_actions;
    overlay_height_in_range = 0;
    unlink_node_if_registered(record_data);
}

/* Update the target using two values from the preceding state block. */
void update_target_from_previous_state(void) {
    s32 *target = &scene_object_payload_alias;
    s32 *source_state = target - 8;


    initialize_effect_record_handlers(target, source_state[2], source_state[3]);
}
