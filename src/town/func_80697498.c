#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800179A0(void);
extern M2C_UNK D_80018FB6;

/* Runs func_800179A0 and returns the address of D_80018FB6. */
s32 *func_80697498(void) {
    func_800179A0();
    return &D_80018FB6;
}
