#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008D024_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Set unk_9A to 0x29 and clear unk_9B and unk_8C. */
void func_80091920(Rec_func_8008D024_arg0 *record) {
    record->unk_9A = 0x29;
    record->unk_9B.as_s8 = 0;
    record->unk_8C = 0;
}
