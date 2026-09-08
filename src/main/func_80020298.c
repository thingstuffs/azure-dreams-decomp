#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8004DCCC();                         /* extern */

/* Process the two embedded records at offsets 4 and 0x10. */
void func_80020298(s32 record_addr) {
    func_8004DCCC(record_addr + 4);
    func_8004DCCC(record_addr + 0x10);
}
