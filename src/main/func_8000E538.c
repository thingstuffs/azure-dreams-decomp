#include "modules/main_server_ship.h"
#include "common.h"

s32 TestEvent(s32);






/* Clear the event status and test the four event handles. */
void card_boot_drain_hardware_events(void) {
    (*(s32 *)(&D_800287E4)) = 0;
    TestEvent((*(s32 *)(&D_80028560)));
    TestEvent((*(s32 *)(&D_80028564)));
    TestEvent((*(s32 *)(&D_80028568)));
    TestEvent((*(s32 *)(&D_8002856C)));
}
