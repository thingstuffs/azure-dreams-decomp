#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80020300(); /* extern */
M2C_UNK func_800C23A8();                            /* extern */

void func_800C23DC(void) {
    func_800C23A8();
    func_80020300(0, 0, 0, 0);
}
