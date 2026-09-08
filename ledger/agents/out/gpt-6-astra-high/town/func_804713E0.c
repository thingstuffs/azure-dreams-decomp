#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_8001B218[];
M2C_UNK func_800190B8();                       /* extern */

/* Pass D_8001B218 to func_800190B8. */
void func_804713E0(void) {
    func_800190B8(D_8001B218);
}
