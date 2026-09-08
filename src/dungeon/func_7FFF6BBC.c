#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009431C_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800920F4;


/* Initialize the record's data pointer and clear its halfword field. */
void func_8009431C(Rec_func_8009431C_arg0 *record) {
    record->unk_00.as_pm = &D_800920F4;
    record->unk_0A = 0;
}
