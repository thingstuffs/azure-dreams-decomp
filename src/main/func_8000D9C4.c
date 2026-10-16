#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Waits for both card channels and requests information for the alternate channel. */
void cardBootToggleChannel(void) {
    s32 card_channel;
    cardBootDrainSoftwareEvents();
    _card_wait(0);
    _card_wait(1);
    card_channel = 0x10 - D_800287CC[0];
    D_800287CC[0] = card_channel;
    cardBootRequestInfo(card_channel);
}
