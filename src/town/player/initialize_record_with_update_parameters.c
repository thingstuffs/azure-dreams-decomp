#include "common.h"
#include "shared/town_handler_entries.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"              /* extern */
void set_player_travel_timing(void *, void *, s32);       /* extern */

/* Initialize the record from fixed data and apply its update parameters. */
void initialize_record_with_update_parameters(s32 record, s32 update_value, s32 init_context) {
    call_the_handler_selects_nonzero_entry(D_800D0130, (struct Rec_func_80094268_arg0 *)(record), (void *)(init_context));
    set_player_travel_timing((void *)(record), (void *)(update_value), init_context);
}
