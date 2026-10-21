#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Set (*(s32 *)(&D_800287E4)) to 2 and return zero. */
s32 card_boot_latch_hardware_status_two(void) {
    (*(s32 *)(&card_hardware_status)) = 2;
    return 0;
}
