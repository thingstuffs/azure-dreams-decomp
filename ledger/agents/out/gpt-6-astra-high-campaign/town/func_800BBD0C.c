#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_80082E76;
/* Request event 0x17 with the low bit of D_80082E76 toggled. */
void func_800B946C(void) {
    func_80041094(0x17, 0, 0, 0, D_80082E76 ^ 1);
}
