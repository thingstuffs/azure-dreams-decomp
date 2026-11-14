#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"



/* Clears the pending flag and returns 4 if it was set, otherwise 0. */
s32 card_boot_timeout_operation(void) {
    s32 status;

    status = 0;
    if (card_operation_state.a != 0) {
        status = 4;
        card_operation_state.a = 0;
    }
    return status;
}
