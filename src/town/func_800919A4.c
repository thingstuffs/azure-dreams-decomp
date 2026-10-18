#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void handle_insert_initialize_two_values_status_flags(Rec_D_800CFCB4 *, s32, s32);                            /* extern */


/* Configure the record and set its mode to 3. */
void configure_the_set_mode_n_3(Rec_D_800CFCB4 *record, s32 setup_value, s32 setup_param) {
    handle_insert_initialize_two_values_status_flags(record, setup_value, setup_param);
    record->unk_14 = 3;
}
