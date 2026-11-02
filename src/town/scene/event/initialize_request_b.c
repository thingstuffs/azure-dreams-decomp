#include "script_symbols.h"
#include "common.h"
#include "town/player/script_flags.h"

extern void set_global_entry_pair(s32 value_18e44, s32 value_18e48); /* placed copy of set_global_entry_pair */
extern s32 apply_selected_entry_values(s32, s32);

/* Initializes the request and processes it when flag 0x50F is set. */
s32 initialize_request(s32 request_id, s32 request_arg) {
    s32 result;

    set_global_entry_pair(request_id, request_arg);
    if (get_script_flag_mask(F_sbs07_pad24) != 0) {
        result = apply_selected_entry_values(request_id, request_arg);
    } else {
        result = 0;
    }
    return result;
}
