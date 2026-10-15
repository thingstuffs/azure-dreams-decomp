#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Waits for both card channels and requests information for the alternate channel. */
void func_800209C4(void) {
    s32 card_channel;
    func_800214A4();
    _card_wait(0);
    _card_wait(1);
    card_channel = 0x10 - D_800287CC[0];
    D_800287CC[0] = card_channel;
    func_800213C4(card_channel);
}
