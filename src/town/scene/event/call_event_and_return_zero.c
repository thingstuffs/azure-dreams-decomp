#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001860C(s32);

/* Calls func_8001860C with 0x998 and returns zero. */
s32 call_event_998_and_return_zero(void) {
    func_8001860C(F_sbs34_pad24);
    return 0;
}
