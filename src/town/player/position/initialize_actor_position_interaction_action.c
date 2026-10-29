#include "common.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/player.h"
#include "town/player/position.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */
extern void town_actor_interaction_address();


/* Set the record field to six, reset and initialize it, and assign its handler. */
void initialize_actor_position_interaction_action(Rec_func_80094268_arg0 *record, s32 unused, s32 setup_value) {
    record->unk_3E.as_s16 = 6;
    store_the_valid_shared_angle_in_offset_hex_10(record);
    call_the_handler_selects_nonzero_entry(D_800D0130, record, (void *)(setup_value));
    record->unk_00.as_pm = &town_actor_interaction_address;
}
