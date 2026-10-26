#include "script_symbols.h"
#include "common.h"
#include "town/scene/event.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 initialize_state_two_entries_pointer(s32 flagIndex);                     /* extern */

/* Calls initialize_state_two_entries_pointer with ID 0x72D. */
s32 initialize_event_position_state(void) {
    return initialize_state_two_entries_pointer(F_sbs20_pad07);
}
