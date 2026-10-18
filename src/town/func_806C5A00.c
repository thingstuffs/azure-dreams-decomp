#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018CEC(s32);

/* Process IDs 0xFCB and 0xFCD, then return success. */
s32 process_event_ids_and_succeed(void) {
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
