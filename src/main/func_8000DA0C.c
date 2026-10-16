#include "modules/main_server_ship.h"
#include "common.h"
#include "m2c_compat.h"



/* Clears (*(s32 *)(&D_800287C8)) and runs cardBootDrainSoftwareEvents. */
void cardBootResetOperationAndDrainEvents(void) {
    (*(s32 *)(&D_800287C8)) = 0;
    cardBootDrainSoftwareEvents();
}
