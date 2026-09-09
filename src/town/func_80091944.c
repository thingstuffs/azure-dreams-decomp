#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8008F01C(Rec_func_80094268_arg0 *, s32, s32);                            /* extern */


/* Configure the record and set its mode to 2. */
void func_8008F0A4(Rec_func_80094268_arg0 *record, s32 setup_value, s32 setup_param) {
    func_8008F01C(record, setup_value, setup_param);
    record->unk_14 = 2;
}
