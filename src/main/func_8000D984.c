#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Waits for both card channels and requests information for the selected channel. */
void cardBootRecheckSelectedChannel(void) {
    cardBootDrainSoftwareEvents();
    _card_wait(0);
    _card_wait(1);
    cardBootRequestInfo((*(s32 *)(&D_800287CC)));
}
