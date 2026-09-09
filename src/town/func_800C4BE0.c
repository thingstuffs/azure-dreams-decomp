#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C22A4();                            /* extern */

/* Run func_sn_ball initialization and reset the four control values. */
void scr_func_sn_ball(void) {
    func_800C22A4();
    func_80020A20(0, 0, 0, 0);
}
