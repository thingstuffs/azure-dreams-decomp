#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "dungeon/globals.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* Returns encounter_cd_ready converted to an unsigned byte. */
u8 get_encounter_cd_ready(void) {
    return (u8) encounter_cd_ready;
}
