#include "modules/main_server_ship.h"
#include "common.h"
s32 TestEvent(s32 event);                         /* extern */





/* Tests the four card event handles. */
void card_boot_drain_software_events(void) {
    TestEvent((*(s32 *)(&D_80028550)));
    TestEvent((*(s32 *)(&D_80028554)));
    TestEvent((*(s32 *)(&D_80028558)));
    TestEvent((*(s32 *)(&D_8002855C)));
}
