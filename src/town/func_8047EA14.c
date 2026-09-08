#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80016A38();                                /* extern */

/* Return whether func_80016A38 returns a value other than -1. */
s32 func_8047EA14(void) {
    return ~func_80016A38() != 0;
}
