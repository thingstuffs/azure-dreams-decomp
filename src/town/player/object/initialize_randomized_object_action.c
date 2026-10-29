#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/player.h"
#include "town/player/object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
#include "engine/window.h"
extern s32 actor_input_interaction_address;


/* Initialize the object state, motion, behavior data, and counter. */
void initialize_randomized_object_action(Rec_func_80094268_arg0 *object, s32 motion, s32 table_arg) {
    object->unk_3E.as_s16 = 6;
    store_the_valid_shared_angle_in_offset_hex_10(object);
    call_the_valid_shared_angle_fixed_hex_120000_context_callee_80094_f_58(motion);
    call_the_handler_selects_nonzero_entry(D_800D0098, object, (void *)(table_arg));
    object->unk_00.as_pm = &actor_input_interaction_address;
    object->unk_0A.as_s16 = (s16) (scale_random_to_unsigned_halfword_limit(2) + 0xC);
}
