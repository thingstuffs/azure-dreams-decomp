#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008F074_arg0.h"

void handle_insert_initialize_two_values_status_flags(Rec_func_8008F074_arg0 *, s32, s32);                            /* extern */


/* Configure the record and set its mode to 1. */
void configure_the_set_mode_n_1(Rec_func_8008F074_arg0 *record, s32 setup_value, s32 setup_param) {
    handle_insert_initialize_two_values_status_flags(record, setup_value, setup_param);
    record->unk_14 = 1;
}
