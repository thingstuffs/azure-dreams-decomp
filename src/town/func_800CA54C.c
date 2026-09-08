#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Clears the record's unk_94 field. */
void func_800C7CAC(Rec_func_80094268_arg0 *record) {
    record->unk_94 = 0;
}
