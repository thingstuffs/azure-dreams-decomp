#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void handle_insert_initialize_two_values_status_flags(Rec_func_80094268_arg0 *, s32, s32);                            /* extern */


/*
 * Initializes the scene-list record with the supplied values and sets its mode byte at offset 0x14
 * to 2.
 */
void configure_the_set_mode_n_2(Rec_func_80094268_arg0 *record, s32 setup_value, s32 setup_param) {
    handle_insert_initialize_two_values_status_flags(record, setup_value, setup_param);
    record->unk_14 = 2;
}
