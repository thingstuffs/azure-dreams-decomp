#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void func_800171D8(u8 *entries);
extern M2C_UNK D_80018AE8;

/* Passes D_80018AE8 to func_800171D8. */
void func_80697800(void) {
    func_800171D8(&D_80018AE8);
}
