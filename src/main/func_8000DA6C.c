#include "modules/main_server_ship.h"
#include "common.h"



/* Sets (*(s32 *)(&D_800287E4)) to 4 and returns zero. */
s32 cardBootLatchHardwareStatusFour(void) {
    (*(s32 *)(&D_800287E4)) = 4;
    return 0;
}
