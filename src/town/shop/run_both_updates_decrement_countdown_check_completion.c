#include "common.h"
#include "m2c_compat.h"

void call_the_same_context_both_processing_routines(s32, s32);            /* extern */
void handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis(void *, void *);            /* extern */
void reset_object_state_passes_selected_result_callee_800_a_00_e_8(); /* extern */

typedef struct S_8009ECF0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009ECF0_0;   /* arg0 in run_both_updates_decrement_countdown_check_completion */

/* Run both updates, decrement the countdown, and check for completion. */
void run_both_updates_decrement_countdown_check_completion(S_8009ECF0_0 *state, s32 update_ctx, s32 update_data, s32 finish_ctx) {
    u16 countdown;

    call_the_same_context_both_processing_routines(update_ctx, update_data);
    handle_resolve_bounding_box_overlaps_linked_colliders_along_least_penetrating_axis((void *)(update_ctx), (void *)(update_data));
    countdown = state->unk_6C - 1;
    state->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        reset_object_state_passes_selected_result_callee_800_a_00_e_8(state, update_ctx, update_data, finish_ctx);
    }
}
