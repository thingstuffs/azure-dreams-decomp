#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80093C58(); /* extern */

/* ext_plsel_kaesu_set: call func_80093C58 with all four arguments cleared. */
void func_800C0B4C(void) {
    func_80093C58(0, 0, 0, 0);
}
