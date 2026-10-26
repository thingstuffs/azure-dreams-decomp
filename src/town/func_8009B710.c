/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s8 town_action_reset_byte;

/*
 * Selects D_800D0170, clears town_action_reset_byte, and installs target_action_update_address
 * with count 0x15.
 */
void init_twenty_one_tick_target_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D0170, record, handler_context);
    town_action_reset_byte = 0;
    record->unk_04.as_pm = &target_action_update_address;
    record->unk_0A.as_s16 = 0x15;
}
