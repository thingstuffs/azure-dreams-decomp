#include "common.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800191E8(s32);                                /* extern */

/* Check whether the queried value is below -47. */
s32 is_check_below_minus_47(s32 query_input) {
    return func_800191E8(query_input) < -0x2F;
}
