#include "common.h"
#include "shared/town_handler_entries.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "town/player.h"

   /* Initialize the record with its handler, count, and a value from the source record. */
void initialize_source_bound_action(TownObjectRecord *record, UnsignedCountdownView *source_record, void *ptr2) {
    dispatch_selected_entry_if_nonzero(D_800D00D0, record, ptr2);
    record->unk_00 = &update_threshold_timed_action;
    record->unk_0A = 5;
    record->unk_34 = (u16) source_record->unk_0A;
}
