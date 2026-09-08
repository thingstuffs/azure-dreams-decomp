#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018CEC();                     /* extern */

/* Call func_80018CEC with IDs 0xFCB and 0xFCD, then return zero. */
s32 func_800169A0(void) {
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
