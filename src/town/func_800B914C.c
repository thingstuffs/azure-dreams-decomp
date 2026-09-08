#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D17C8;

/* Returns the indexed entry from D_800D17C8. */
s32 func_800B68AC(s32 index) {
    return *(M2C_UNK *)((u8 *)&D_800D17C8 + ((index) * 4));
}
