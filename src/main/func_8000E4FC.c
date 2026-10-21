#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"
#include "main.h"



/* Returns the pending card status and processes it when nonzero. */
s32 card_boot_take_hardware_status(void) {
    s32 card_status;

    card_status = 0;
    if ((*(s32 *)(&card_hardware_status)) != 0) {
        card_status = (*(s32 *)(&card_hardware_status));
        card_boot_drain_hardware_events();
    }
    return card_status;
}
