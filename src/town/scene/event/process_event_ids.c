#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018CEC(s32);

/* Process IDs 0xFCB and 0xFCD through func_80018CEC, then return zero. */
s32 process_event_ids(void) {
    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    return 0;
}
