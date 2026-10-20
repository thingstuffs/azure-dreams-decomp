#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 initialize_state_two_entries_pointer();                         /* extern */

/* Calls initialize_state_two_entries_pointer with ID 0x98F and returns its result. */
s32 select_data_array_based_flag(void) {
    return initialize_state_two_entries_pointer(0x98F);
}
