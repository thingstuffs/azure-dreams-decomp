#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"
#include "main.h"



/* Waits for both card channels and requests information for the alternate channel. */
void card_boot_toggle_channel(void) {
    s32 card_channel;
    card_boot_drain_software_events();
    _card_wait(0);
    _card_wait(1);
    card_channel = 0x10 - card_selected_channel_alias[0];
    card_selected_channel_alias[0] = card_channel;
    card_boot_request_info(card_channel);
}
