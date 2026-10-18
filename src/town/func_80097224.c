#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern void call_the_selected_nonzero_table_callee_80094_a_38(s32 *, Rec_func_80094268_arg0 *);


/* Call the handler when the record selects a nonzero entry. */
void call_the_handler_selects_nonzero_entry(s32 *entries, Rec_func_80094268_arg0 *record, void *ptr2) {
    if (entries[record->unk_16] != 0) {
        call_the_selected_nonzero_table_callee_80094_a_38(entries, record);
    }
}
