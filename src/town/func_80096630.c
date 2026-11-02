/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"

extern s32 D_80090C68;

/* Selects D_800D0180 and installs D_80090C68 with action count 0x15. */
void init_flagged_entity_action(TownObjectRecord *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry(D_800D0180, record, handler_context);
    record->unk_00.as_pm = &D_80090C68;
    record->unk_0A.as_s16 = 0x15;
}
