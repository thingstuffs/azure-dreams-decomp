#include "common.h"
#include "m2c_compat.h"

s32 townInitializeSharedStateFromTable(); /* extern */

/* koya_mon_status_open: Opens the hut monster status display. */
void koya_mon_status_open(void) {
    townInitializeSharedStateFromTable(0, 0, 0, 0);
}
