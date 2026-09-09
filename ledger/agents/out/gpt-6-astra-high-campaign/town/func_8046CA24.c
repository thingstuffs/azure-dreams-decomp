#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001DA48(s32, s32);                                /* extern */

/* Return whether func_8001DA48 produces a value other than -1. */
s32 func_8046CA24(s32 first_input, s32 second_input) {
    return ~func_8001DA48(first_input, second_input) != 0;
}
