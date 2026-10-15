#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Waits for both card channels and requests information for the selected channel. */
void func_80020984(void) {
    func_800214A4();
    _card_wait(0);
    _card_wait(1);
    func_800213C4((*(s32 *)(&D_800287CC)));
}
