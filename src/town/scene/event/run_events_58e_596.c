#include "script_symbols.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800177C4(s32);

/* Call func_800177C4 for IDs 0x58E and 0x596 in order. */
void run_events_58e_596(void) {
    func_800177C4(F_sbs10_pad22);
    func_800177C4(F_sbs10_pad30);
}
