/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"

extern s32 town_timed_state_address;

void init_timed_dispatch_action(TownObjectRecord *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry(counted_action_handler_table, record, handler_context);
    record->unk_00.as_pm = &town_timed_state_address;
    record->unk_0A.as_s16 = 0xA;
}
