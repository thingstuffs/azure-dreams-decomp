#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001979C(s32, s32, s32, s32);                                /* extern */

/* Return whether func_8001979C produces a value other than -1. */
s32 func_80472778(s32 first_input, s32 second_input, s32 third_input, s32 fourth_input) {
    return ~func_8001979C(first_input, second_input, third_input, fourth_input) != 0;
}
