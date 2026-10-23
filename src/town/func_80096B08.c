/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_80091F64;

void initialize_action_object_type_three(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) type_three_action_handler_table, record, ptr2);
    record->unk_00.as_pm = &D_80091F64;
    record->unk_0A.as_s16 = 3;
}
