/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"
#include "town/player/position_handlers.h"



/* Selects D_800D00D0 and installs D_80091A08 with action count 6. */
void init_threshold_countdown_action(TownObjectRecord *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry(D_800D00D0, record, handler_context);
    record->unk_00.as_pm = update_threshold_countdown_action;
    record->unk_0A.as_s16 = 6;
}
