#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80017354();                                /* extern */

/* Return whether func_80017354 returns a value other than -1. */
s32 func_8065CB30(void) {
    return ~func_80017354() != 0;
}
