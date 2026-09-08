#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800A56E0();                     /* extern */

/* Select buffered entry 0 in mode 1 and issue request 0x200. */
void func_800F67F4(void) {
    func_8004437C(0, 1);
    func_800A56E0(0x200);
}
