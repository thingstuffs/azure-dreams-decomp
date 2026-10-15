#include "modules/main_server_ship.h"
#include "common.h"



/* Sets (*(s32 *)(&D_800287E4)) to one and returns zero. */
s32 func_80020A30(void) {
    (*(s32 *)(&D_800287E4)) = 1;
    return 0;
}
