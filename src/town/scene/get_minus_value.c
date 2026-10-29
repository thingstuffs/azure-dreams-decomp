#include "common.h"
#include "town/scene.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800190DC(void);                                /* extern */

/* Returns 20 minus the value from func_800190DC. */
s32 get_20_minus_value(void) {
    return 0x14 - func_800190DC();
}
