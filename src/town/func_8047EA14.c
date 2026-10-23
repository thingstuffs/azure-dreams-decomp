#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80016A38();                                /* extern */

/* Return whether func_80016A38 returns a value other than -1. */
s32 check_scene_query_result(void) {
    return ~func_80016A38() != 0;
}
