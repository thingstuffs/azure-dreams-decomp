#include "script_symbols.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018A64(s32);

/* Call func_80018A64 with IDs 0x1476 and 0x5C3 in sequence. */
void run_events_1476_5c3(void) {
    func_80018A64(Ft_vivian_love);
    func_80018A64(F_sbs11_pad32);
}
