#include "common.h"
#include "town/event/object.h"
#include "town/shop/state.h"

extern s32 process_the_item_index_available_report_success(s32 context, void *subject, s32 motion, s32 extra, void *scratch);

// Clear the subject flag and run the fallback actor handler if the check fails.
void clear_subject_flag_and_run_fallback(s32 actor, void *subject, s32 motion, s32 context) {
    s32 scratch[6];

    *((s8 *)subject + 0x15) = 0;
    if (process_the_item_index_available_report_success(actor, subject, motion, context, scratch) == 0) {
        select_object_value_by_height_band(actor, subject, motion, context);
    }
}
