#include "common.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 get_current_nested_record_value(s32);                                /* extern */

/* Check whether the queried value is below -47. */
s32 is_check_below_minus_47(s32 query_input) {
    return get_current_nested_record_value(query_input) < -0x2F;
}
