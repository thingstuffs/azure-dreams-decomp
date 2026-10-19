#include "common.h"
#include "shared/town_dispatch_data.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_800171D8(u8 *entries);

/* Passes D_80018AE8 to func_800171D8. */
void func_80697800(void) {
    func_800171D8(&D_80018AE8);
}
