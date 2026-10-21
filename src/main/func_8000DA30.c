#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"



/* Sets (*(s32 *)(&D_800287E4)) to one and returns zero. */
s32 card_boot_latch_hardware_status_one(void) {
    (*(s32 *)(&card_hardware_status)) = 1;
    return 0;
}
