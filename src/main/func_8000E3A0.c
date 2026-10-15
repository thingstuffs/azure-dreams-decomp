#include "modules/main_server_ship.h"
#include "common.h"



/* Clears a pending flag and returns 5 if it was set, or 0 otherwise. */
s32 func_800213A0(void) {
    s32 status;

    status = 0;
    if (D_800287C8.a != 0) {
        status = 5;
        D_800287C8.a = 0;
    }
    return status;
}
