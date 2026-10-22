#include "common.h"
#include "town/player.h"

extern void apply_selected_entry_values(s32 record, s32 entry_index);
extern void set_current_entry_script_flag(void);

/* Process the request after checking the threshold of 25. */
void process_request_checking_threshold_25(s32 request, s32 context) {
    if (get_linked_record_field_2_d_60() >= 0x19) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(request, context);
}
