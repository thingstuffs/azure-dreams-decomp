/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/action_reset_data.h"
#include "town/player/object_initialization_g00546.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"


/*
 * Selects D_800D0170, clears town_action_reset_byte, and installs target_action_update_address
 * with count 0x15.
 */
void init_twenty_one_tick_target_action(TownObjectRecord *record, void *unused, void *handler_context) {
    dispatch_selected_entry_if_nonzero(D_800D0170, record, handler_context);
    town_action_reset_byte = 0;
    record->unk_04 = &target_action_update_address;
    record->unk_0A = 0x15;
}
