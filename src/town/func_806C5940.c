#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80018CEC(s32);

/* Process IDs 0xFCB and 0xFCD through func_80018CEC, then return zero. */
s32 process_event_ids(void) {
    func_80018CEC(0xFCB);
    func_80018CEC(0xFCD);
    return 0;
}
