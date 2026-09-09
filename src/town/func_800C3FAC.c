#include "common.h"
#include "m2c_compat.h"

M2C_UNK town_sd_sq_callagain_sub();                     /* extern */

/* town_sd_sq_callagain: replay the town sequence with flags 0x9000. */
void town_sd_sq_callagain(void) {
    town_sd_sq_callagain_sub(0x9000);
}
