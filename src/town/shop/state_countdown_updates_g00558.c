/* State countdown updates (G00558). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A1510. */
#include "town/shop/state_countdown_updates_g00558.h"
#include "town/shop.h"

/* Resets object state and passes the selected result to select_a_town_entry_writes_root_relative_coordinates_output. */
void reset_object_state_passes_selected_result_callee_800_a_00_e_8(void *object, void *status, void *context, s32 unused_finish_ctx) {
    s32 result;
    *((s8 *)status + 0x15) = 0;
    *(s32 *)((u8 *)context + 0xC) = 0;
    *(s32 *)((u8 *)context + 0x10) = 0;
    *(s32 *)((u8 *)context + 0x14) = 0;
    *(s32 **)((u8 *)object + 0x50) = &D_8009ED7C;
    *(s16 *)((u8 *)object + 0x6C) = 0xA;
    if (*((u8 *)object + 0x4D) == 0x13) {
        result = D_80100B3B;
    } else {
        result = get_nearest_unflagged_s_result_n_1_none_available(find_target_byte_index_in_list(), context);
    }
    select_a_town_entry_writes_root_relative_coordinates_output(result);
}

/*
 * Runs both context updates and resolves collider overlap, then decrements the 16-bit countdown
 * and resets object state when the signed result is zero or negative.
 */
void run_both_updates_decrement_countdown_check_completion(S_8009ECF0_0 *state, s32 update_ctx, s32 update_data, s32 finish_ctx) {
    u16 countdown;

    call_the_same_context_both_processing_routines(update_ctx, update_data);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis((void *)(update_ctx), (void *)(update_data));
    countdown = state->unk_6C - 1;
    state->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        reset_object_state_passes_selected_result_callee_800_a_00_e_8(state, (void *)update_ctx, (void *)update_data, finish_ctx);
    }
}
