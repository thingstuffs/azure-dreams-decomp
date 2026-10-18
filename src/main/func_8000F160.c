#include "modules/main_server_ship.h"
#include "common.h"



/* Counts nonzero entries across five records. */
s32 card_boot_count_cached_slots(void) {
    s32 i;
    s32 active_count;

    active_count = 0;
    for (i = 0; i < 5; i++) {
        if ((*(s32 (*)[])(&D_80083E98))[i * 0x20] != 0) {
            active_count += 1;
        }
    }
    return active_count;
}
