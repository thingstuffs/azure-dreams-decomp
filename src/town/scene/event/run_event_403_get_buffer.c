#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800197D8(s32, ...);
extern M2C_UNK D_8001A054;

/* Pass 0x403 to func_800197D8 and return the address of D_8001A054. */
s32 *run_event_403_get_buffer(void) {
    func_800197D8(0x403);
    return &D_8001A054;
}
