/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s8 town_action_reset_byte;
extern s32 record_action_update_address;

/*
 * Selects D_800D0180, clears town_action_reset_byte, and installs record_action_update_address
 * with count 0x15.
 */
void init_twenty_one_tick_record_action_b(Rec_func_80094268_arg0 *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D0180, record, handler_context);
    town_action_reset_byte = 0;
    record->unk_04.as_pm = &record_action_update_address;
    record->unk_0A.as_s16 = 0x15;
}
