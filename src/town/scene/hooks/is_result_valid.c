#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018CA8();                                /* extern */

/* Returns whether func_80018CA8 returns a value other than -1. */
s32 is_result_valid(void) {
    return ~func_80018CA8() != 0;
}
