#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8009FDBC();                            /* extern */
M2C_UNK func_8009FE84();                            /* extern */

/* Calls func_8009FDBC followed by func_8009FE84. */
void func_8009FF28(void) {
    func_8009FDBC();
    func_8009FE84();
}
