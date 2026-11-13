/* State countdown updates. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A1510. */
#include "town/shop/state_countdown_updates_g00558.h"
#include "town/shop.h"
#include "town/scene/motion.h"
#include "town/shop_callbacks_api.h"

/* Resets object state and passes the selected result to set_shop_target_to_entry. */
void retarget_entity_to_nearest_entry(void *object, TownObjectRecord *status, ObjectPosition *position, s32 unused_finish_ctx) {
    s32 result;
    status->unk_15 = 0;
    position->velocity_x = 0;
    position->velocity_y = 0;
    position->velocity_z = 0;
    *(s32 **)((u8 *)object + 0x50) = move_toward_target_finalize_countdown_expires;
    *(s16 *)((u8 *)object + 0x6C) = 0xA;
    if (*((u8 *)object + 0x4D) == 0x13) {
        result = D_80100B3B;
    } else {
        result = find_nearest_unflagged_record_result(find_target_byte_index_in_list(), position);
    }
    set_shop_target_to_entry(result);
}

/*
 * Runs both context updates and resolves collider overlap, then decrements the 16-bit countdown
 * and resets object state when the signed result is zero or negative.
 */
void update_entity_until_countdown_ends(S_8009ECF0_0 *state, s32 update_ctx, ObjectPosition *position, s32 finish_ctx) {
    u16 countdown;

    apply_bound_adjustments(update_ctx, (s32)position);
    resolve_collider_overlaps((void *)(update_ctx), position);
    countdown = state->unk_6C - 1;
    state->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        retarget_entity_to_nearest_entry(state, (void *)update_ctx, position, finish_ctx);
    }
}
