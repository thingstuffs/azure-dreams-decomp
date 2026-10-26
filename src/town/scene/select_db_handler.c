#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern s32 apply_selected_entry_values(void *, s32);

/* Select the handler for 0xDB8 based on the query result and return its truth value. */
s32 select_db_8_handler(void *object, s32 query_value) {
    s32 result;

    if (apply_selected_entry_values(object, query_value) == 0) {
        set_script_flag_bit(Ftt_pad136);
        result = 0;
    } else {
        clear_script_flag_bit(Ftt_pad136);
        result = 1;
    }
    return result;
}
