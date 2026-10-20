#include "script_symbols.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800197D8(s32, ...);

/* Call func_800197D8 with 0x400. */
void run_event_400(void) {
    func_800197D8(F_sbs01_pad11);
}
