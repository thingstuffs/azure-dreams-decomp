#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"

s32 _card_info();                             /* extern */



/* Retries the card information request until accepted and resets the request state. */
s32 card_boot_request_info(s32 card_channel) {
    card_boot_drain_software_events();
    do {

    } while (_card_info(card_channel) == 0);
    D_800287E0[0] = 0;
    (*(s32 (*)[])(&D_800287C8))[0] = 1;
    return 1;
}
