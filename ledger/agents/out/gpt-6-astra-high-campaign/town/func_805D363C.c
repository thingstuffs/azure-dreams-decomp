#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800191E8(s32);                                /* extern */

/* Check whether the queried value is below -47. */
s32 func_805D363C(s32 query_input) {
    return func_800191E8(query_input) < -0x2F;
}
