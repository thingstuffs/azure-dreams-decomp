#include "modules/main_server_ship.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Set (*(s32 *)(&D_800287E4)) to 3 and return zero. */
s32 cardBootLatchHardwareStatusThree(void) {
    (*(s32 *)(&D_800287E4)) = 3;
    return 0;
}
