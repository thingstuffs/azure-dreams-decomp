#include "script_symbols.h"
#include "common.h"

#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
extern u8 town_entry_check_zero[];

/* Record whether the check returned zero and invoke the handler when it did. */
s32 record_check_returned(void *check_input_1, s32 check_input_2) {
    s32 result;

    result = process_checked_entry(check_input_1, check_input_2);
    if (result != 0) {
        town_entry_check_zero[0] = 0;
    } else {
        town_entry_check_zero[0] = 1;
        clear_script_flag_bit(Ftt_pad73);
    }
    return result;
}
