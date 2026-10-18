#include "modules/main_server_ship.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Returns the first value in (*(s32 (*)[])(&D_800287C8)). */
s32 card_boot_get_operation_state(void) {
    return *(*(s32 (*)[])(&D_800287C8));
}
