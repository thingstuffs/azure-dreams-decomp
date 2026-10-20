#include "common.h"
#include "m2c_compat.h"

s32 create_an_position_initializes_graphics_state();                     /* extern */
void *get_address_global_80100_aa_0();                              /* extern */
void handle_shift_entries_left_until_free_entry_limit_clear_tail(void);                            /* extern */

typedef struct S_800A0504_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0504_0;

/* Run the follow-up action when the current record has an eligible type and passes the check. */
void run_the_follow_up_action_has_eligible_type_passes_check(s32 check_value) {
    u8 record_type;
    S_800A0504_0 *record;

    record = get_address_global_80100_aa_0();
    record_type = record->unk_01;
    if ((record_type != 0) && (record_type != 0x13) && (create_an_position_initializes_graphics_state(record, check_value) != 0)) {
        handle_shift_entries_left_until_free_entry_limit_clear_tail();
    }
}
