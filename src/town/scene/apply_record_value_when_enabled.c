#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"
#include "town/player.h"

s32 apply_selected_entry_values(Rec_func_800165F4_arg0 *record, s32 entry_index);             /* extern */


/* Conditionally process the record ID before passing the record to apply_selected_entry_values. */
void apply_record_value_when_enabled(Rec_func_800165F4_arg0 *record, s32 handler_context) {
    if (get_linked_record_field_2_d_60() != 0) {
        set_script_flag_bit(record->unk_18);
    }
    apply_selected_entry_values(record, handler_context);
}
