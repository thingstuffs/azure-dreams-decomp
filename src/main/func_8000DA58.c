#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"

/* Set (*(s32 *)(&card_hardware_status)) to 3 and return zero. */
s32 card_boot_latch_hardware_status_three(void) {
    (*(s32 *)(&card_hardware_status)) = 3;
    return 0;
}
