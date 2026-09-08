#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018FDC();                /* extern */

/* Forwards the index plus four to func_80018FDC with mode 1. */
void func_804720B8(s32 index) {
    func_80018FDC(index + 4, 1);
}
