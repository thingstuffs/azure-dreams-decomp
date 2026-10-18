#include "common.h"
#include "m2c_compat.h"

void call_the_handler_selects_nonzero_entry();              /* extern */
void set_player_travel_timing();       /* extern */
extern M2C_UNK D_800D0130;

/* Initialize the record from fixed data and apply its update parameters. */
void initialize_record_with_update_parameters(s32 record, s32 update_value, s32 init_context) {
    call_the_handler_selects_nonzero_entry(&D_800D0130, record, init_context);
    set_player_travel_timing(record, update_value, init_context);
}
