#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800B3440();                         /* extern */

/* Passes the base plus 0x20 to func_800B3440. */
void func_800B3488(s32 base) {
    func_800B3440(base + 0x20);
}
