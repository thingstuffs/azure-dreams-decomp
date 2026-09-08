#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800B4B7C();                         /* extern */

/* Calls func_800B4B7C with the offset advanced by 0x20. */
void func_800B4BC4(s32 offset) {
    func_800B4B7C(offset + 0x20);
}
