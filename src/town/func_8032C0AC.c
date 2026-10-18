#include "common.h"
#include "m2c_compat.h"

void apply_selected_entry_values(s32, s32);             /* extern */
void set_current_entry_script_flag(void);                 /* extern */
s32 get_linked_record_field_2_d_60(void);                  /* extern */

/* Process the request after checking the threshold of 15. */
void process_request_after_threshold_15(s32 request, M2C_UNK context) {
    if (get_linked_record_field_2_d_60() >= 0xF) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(request, context);
}
