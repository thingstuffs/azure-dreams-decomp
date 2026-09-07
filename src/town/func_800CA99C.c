#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s8 D_80082680;
M2C_UNK func_800C7C88();                            /* extern */

void func_800C80FC(void) {
    D_80082680 = 0;
    func_800C7C88();
}
