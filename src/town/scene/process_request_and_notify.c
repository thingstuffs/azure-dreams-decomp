#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

s32 apply_selected_entry_values(void *, s32);                                /* extern */
void write_script_flag_range(s32 base, s32 bits, s32 count);   /* extern */

/* Process the request and invoke write_script_flag_range when the result is nonzero. */
s32 process_request_and_notify(void *context, s32 request) {
    s32 result;

    result = apply_selected_entry_values(context, request);
    if (result != 0) {
        write_script_flag_range(Ftt_pad61, 3, 2);
    }
    return result;
}
