#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Waits for both card channels and requests information for the selected channel. */
void card_boot_recheck_selected_channel(void) {
    card_boot_drain_software_events();
    _card_wait(0);
    _card_wait(1);
    card_boot_request_info((*(s32 *)(&D_800287CC)));
}
