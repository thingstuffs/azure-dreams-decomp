#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800A56E0();                     /* extern */

/* Selects buffered entry 0x2A in mode 1, then dispatches request 0x200. */
void func_800F6820(void) {
    func_8004437C(0x2A, 1);
    func_800A56E0(0x200);
}
