#include "script_symbols.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_800198D0(s32);

/* Call func_800198D0 with the fixed argument 0x14. */
void run_event_14(void) {
    func_800198D0(sn_open_sekkyo_end);
}
