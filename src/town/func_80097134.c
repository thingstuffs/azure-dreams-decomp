/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_800935BC;

void init_target_tile_action(Rec_func_80094268_arg0 *record, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) type_three_action_handler_table, record, handler_context);
    record->unk_00.as_pm = &D_800935BC;
    record->unk_0A.as_s16 = 0xA;
}
