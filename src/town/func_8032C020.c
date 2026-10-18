#include "common.h"

extern s32 get_linked_record_field_2_d_60(void);
extern s32 set_current_entry_script_flag();
extern s32 apply_selected_entry_values();

/* Run the preliminary callback at a count of ten or more, then dispatch the argument pair. */
void run_preliminary_callback_count_ten(s32 dispatch_value, s32 dispatch_option) {
    if (get_linked_record_field_2_d_60() >= 10) {
        set_current_entry_script_flag();
    }
    apply_selected_entry_values(dispatch_value, dispatch_option);
}
