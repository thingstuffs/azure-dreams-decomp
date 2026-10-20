#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 initialize_state_two_entries_pointer();                     /* extern */

/* Calls initialize_state_two_entries_pointer with ID 0x72D. */
void initialize_event_position_state(void) {
    initialize_state_two_entries_pointer(F_sbs20_pad07);
}
