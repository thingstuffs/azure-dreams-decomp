#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Clears (*(s32 *)(&D_800287C8)) and runs card_boot_drain_software_events. */
void card_boot_reset_operation_and_drain_events(void) {
    (*(s32 *)(&D_800287C8)) = 0;
    card_boot_drain_software_events();
}
