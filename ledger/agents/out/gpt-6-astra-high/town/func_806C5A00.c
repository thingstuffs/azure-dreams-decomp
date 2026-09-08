#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018CEC();                     /* extern */

/* Process IDs 0xFCB and 0xFCD, then return success. */
s32 func_80016A00(void) {
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
