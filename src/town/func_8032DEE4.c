#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8001DD74(s32, s32, s32, s32);                            /* extern */

/* Forward four values to func_8001DD74 and return zero. */
s32 func_800186E4(s32 first_value, s32 second_value, s32 third_value, s32 fourth_value) {
    func_8001DD74(first_value, second_value, third_value, fourth_value);
    return 0;
}
