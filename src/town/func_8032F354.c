#include "common.h"
#include "records/Rec_func_800165F4_arg0.h"


typedef struct S_80019B54_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019B54_1;   /* (arg1 * 0x10) + ((Rec_func_800165F4_arg0 *)arg0)->unk_10 in apply_selected_entry_values */


extern s32 check_record_flag_if_unblocked(Rec_func_800165F4_arg0 *);
extern s32 set_script_flag_bit(s16 value);
extern s32 clear_script_flag_bit(s16 value);

/* Apply the selected entry and record values if the record passes its check. */
s32 apply_selected_entry_values(Rec_func_800165F4_arg0 *record, s32 entry_index) {
    if (check_record_flag_if_unblocked(record) != 0) {
        set_script_flag_bit(((S_80019B54_1 *)((entry_index * 0x10) + record->unk_10))->unk_0C);
        clear_script_flag_bit(record->unk_18);
        return 1;
    }
    return 0;
}
