#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s8 encounter_cd_ready;
/* Returns D_8017397C as an unsigned byte. */
u8 get_unsigned_transition_byte(void) {
    return (u8) encounter_cd_ready;
}
