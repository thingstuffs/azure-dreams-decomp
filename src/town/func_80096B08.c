/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/town_handler_entries.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

extern s32 D_80091F64;

/* Selects type_three_action_handler_table and installs D_80091F64 with action count 3. */
void initialize_action_object_type_three(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry(type_three_action_handler_table, record, ptr2);
    record->unk_00.as_pm = &D_80091F64;
    record->unk_0A.as_s16 = 3;
}
