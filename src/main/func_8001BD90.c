#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80402BB8();                         /* extern */
M2C_UNK func_80402CD4();                    /* extern */

void func_8001BD90(s32 arg0) {
    func_80402CD4(arg0 + 0x24, arg0);
    func_80402BB8(arg0);
}
