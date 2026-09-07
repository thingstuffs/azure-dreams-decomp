#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80019184[];
M2C_UNK func_80017BA0();                            /* extern */

s32 *func_80016E18(void) {
    func_80017BA0();
    return D_80019184;
}
