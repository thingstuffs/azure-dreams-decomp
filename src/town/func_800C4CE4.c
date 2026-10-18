#include "modules/town_minigame_dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass the town resource to handler 6 and finalize the operation. */
void finalize_town_resource_operation(void) {
    Control_CD(6, &D_800D4750, 0);
    drain_cd_command_queue();
}
