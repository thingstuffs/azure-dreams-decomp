#include "modules/main_server_ship.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Set (*(s32 *)(&D_800287E4)) to 2 and return zero. */
s32 func_80020A44(void) {
    (*(s32 *)(&D_800287E4)) = 2;
    return 0;
}
