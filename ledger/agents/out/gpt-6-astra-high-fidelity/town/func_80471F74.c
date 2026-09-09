#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018BE4(s32 arg0, s32 arg1, s32 arg2, s32 arg3); /* extern */
M2C_UNK func_80018C58();                            /* extern */

void func_80471F74(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_80018BE4(arg0, arg1, arg2, arg3);
    func_80018C58();
}
