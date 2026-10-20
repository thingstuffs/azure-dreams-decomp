#include "common.h"
s32 town_sd_sq_callagain_sub(s32 sequence_flags);                     /* extern */

/* town_sd_sq_callagain: replay the town sequence with flags 0x9000. */
void town_sd_sq_callagain(void) {
    town_sd_sq_callagain_sub(0x9000);
}
