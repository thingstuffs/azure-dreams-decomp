#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"
#include "main.h"



/* Clears card_operation_state and drains the software event queue. */
void card_boot_reset_operation_and_drain_events(void) {
    (*(s32 *)(&card_operation_state)) = 0;
    card_boot_drain_software_events();
}
