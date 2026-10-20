#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 apply_selected_entry_values();             /* extern */
void set_script_flag_bit();                         /* extern */
s32 get_script_flag_mask();                         /* extern */


/* Apply the record field when the query for 0x1451 succeeds, then process the record. */
void apply_conditional_record_value(Rec_func_800165F4_arg0 *record, s32 context) {
    if (get_script_flag_mask(F_sb34_00) != 0) {
        set_script_flag_bit(record->unk_18);
    }
    apply_selected_entry_values(record, context);
}
