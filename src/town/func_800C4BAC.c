#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_800C22A4();                            /* extern */

/* Run start_tako_func initialization and reset the four control values. */
void start_tako_func(void) {
    func_800C22A4();
    func_800254A4(0, 0, 0, 0);
}
