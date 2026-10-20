#include "common.h"

extern s32 apply_selected_entry_values();
extern void set_current_entry_script_flag();
extern s32 get_linked_record_field_2_d_60();

/* Process the request after checking the threshold of 20. */
void process_request_after_threshold_20(s32 request, s32 context) {
    if (get_linked_record_field_2_d_60() >= 0x14) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(request, context);
}
