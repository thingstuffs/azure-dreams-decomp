/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"
#include "town/player/position_handlers.h"


extern s32 D_800D00D8;

/* Selects D_800D00D8 and installs D_80091CE0 with action count 1. */
void init_countdown_handler_action(TownObjectRecord *record, void *unused, void *handler_context) {
    dispatch_selected_entry_if_nonzero(&D_800D00D8, record, handler_context);
    record->unk_00 = invoke_handler_when_countdown_expires;
    record->unk_0A = 1;
}
