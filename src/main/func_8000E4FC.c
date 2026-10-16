#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Returns the pending card status and processes it when nonzero. */
s32 cardBootTakeHardwareStatus(void) {
    s32 card_status;

    card_status = 0;
    if ((*(s32 *)(&D_800287E4)) != 0) {
        card_status = (*(s32 *)(&D_800287E4));
        cardBootDrainHardwareEvents();
    }
    return card_status;
}
