#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018CEC();                     /* extern */

/* Process IDs 0xFCB and 0xFCD through func_80018CEC, then return zero. */
s32 func_80016940(void) {
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
