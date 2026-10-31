#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"
#include "shared/entity.h"
#include "shared/position_views.h"
#include "town/player.h"

   /* Initialize the record with its handler, count, and a value from the source record. */
void initialize_source_bound_action(Rec_func_80094268_arg0 *record, UnsignedCountdownView *source_record, void *ptr2) {
    call_the_handler_selects_nonzero_entry(D_800D00D0, record, ptr2);
    record->unk_00.as_pm = &update_threshold_timed_action;
    record->unk_0A.as_s16 = 5;
    record->unk_34.as_u16 = (u16) source_record->unk_0A;
}
