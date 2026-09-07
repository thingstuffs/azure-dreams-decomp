#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018570();                     /* extern */
s32 func_80018668();                         /* extern */

s32 func_804801D0(void) {
    s32 temp_s0;

    temp_s0 = func_80018668(0x146C);
    func_80018570(0x146C);
    return temp_s0;
}
