#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 clear_script_flag_bit(s32);

/* Process IDs 0xFCB and 0xFCD through func_80018CEC, then return zero. */
s32 process_event_ids(void) {
    clear_script_flag_bit(F_cheriru_first_cheriru);
    clear_script_flag_bit(F_cheriru_first_nadia);
    return 0;
}
