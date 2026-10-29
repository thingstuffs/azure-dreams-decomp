#ifndef TOWN_SHOP_STATE_COUNTDOWN_UPDATES_G00558_H
#define TOWN_SHOP_STATE_COUNTDOWN_UPDATES_G00558_H
/* State countdown updates declarations (G00558). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A1510. */

#include "common.h"
#include "town/scene/collision.h"
#include "m2c_compat.h"

/* extern */
typedef struct S_8009ECF0_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_8009ECF0_0;

extern s32 get_nearest_unflagged_s_result_n_1_none_available(s32 record_set, void *target);
extern s32 D_8009ED7C;
extern u8 D_80100B3B;
void call_the_same_context_both_processing_routines(s32, s32);
/* extern */

/* Functions defined in this translation unit. */
void reset_object_state_passes_selected_result_callee_800_a_00_e_8(void *object, void *status, void *context, s32 unused_finish_ctx);
void run_both_updates_decrement_countdown_check_completion(S_8009ECF0_0 *state, s32 update_ctx, s32 update_data, s32 finish_ctx);

#endif
