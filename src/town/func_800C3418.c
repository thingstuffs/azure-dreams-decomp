#include "common.h"
#include "m2c_compat.h"

s32 initialize_shared_state_from_table(); /* extern */

/* koya_mon_status_open: Opens the hut monster status display. */
void koya_mon_status_open(void) {
    initialize_shared_state_from_table(0, 0, 0, 0);
}
