#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/script_flags.h"

s32 apply_selected_entry_values();                /* extern */
void set_current_entry_script_flag(void);                            /* extern */

/* Conditionally reset the subsystem, select 0xD7F, and forward the request. */
void reset_and_dispatch_request(s32 request, s32 request_data) {
    if (get_linked_record_field_2_d_60() >= 5) {
        set_current_entry_script_flag();
    }
    set_script_flag_bit(Ftt_pad78);
    apply_selected_entry_values(request, request_data);
}
