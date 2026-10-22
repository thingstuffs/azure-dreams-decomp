#include "common.h"
#include "town/player.h"

void apply_selected_entry_values(s32, s32);             /* extern */
void set_current_entry_script_flag(void);                 /* extern */

/* Process the request after checking the threshold of 15. */
void process_request_after_threshold_15(s32 request, s32 context) {
    if (get_linked_record_field_2_d_60() >= 0xF) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(request, context);
}
