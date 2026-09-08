#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800B47BC();                         /* extern */

/* Calls func_800B47BC with the value increased by 0x20. */
void func_800B4898(s32 value) {
    func_800B47BC(value + 0x20);
}
