#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018BE4(s32 value0, s32 value1, s32 value2, s32 value3); /* extern */
M2C_UNK func_80018C58();                            /* extern */

void func_80471F74(s32 value0, s32 value1, s32 value2, s32 value3) {
    func_80018BE4(value0, value1, value2, value3);
    func_80018C58();
}
