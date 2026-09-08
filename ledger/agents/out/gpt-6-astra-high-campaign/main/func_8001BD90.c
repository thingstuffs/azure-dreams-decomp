#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80402BB8();                         /* extern */
M2C_UNK func_80402CD4();                    /* extern */

/* Process the embedded data at offset 0x24, then the containing object. */
void func_8001BD90(s32 object_addr) {
    func_80402CD4(object_addr + 0x24, object_addr);
    func_80402BB8(object_addr);
}
