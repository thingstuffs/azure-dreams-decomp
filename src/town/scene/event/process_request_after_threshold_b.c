#include "common.h"
#include "town/player.h"

extern s32 apply_selected_entry_values();
extern void set_current_entry_script_flag();

/*
 * Sets the current entry script flag when the linked record field reaches 20, then applies the
 * selected entry values regardless of the threshold.
 */
void process_request_after_threshold_20(s32 request, s32 context) {
    if (get_linked_record_field_2_d_60() >= 0x14) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(request, context);
}
