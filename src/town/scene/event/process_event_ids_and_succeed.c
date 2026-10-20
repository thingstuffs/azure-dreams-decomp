#include "script_symbols.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018CEC(s32);

/* Process IDs 0xFCB and 0xFCD, then return success. */
s32 process_event_ids_and_succeed(void) {
    func_80018CEC(F_cheriru_first_cheriru);
    func_80018CEC(F_cheriru_first_nadia);
    return 0;
}
