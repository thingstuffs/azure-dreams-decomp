#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800930E4;


/* Initializes the record with D_800930E4 and a value of 0x13. */
void func_800946FC(Rec_func_80094268_arg0 *record) {
    record->unk_00.as_pm = &D_800930E4;
    record->unk_0A.as_s16 = 0x13;
}
