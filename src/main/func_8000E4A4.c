#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"
s32 TestEvent(s32 event);                         /* extern */





/* Tests the four card event handles. */
void card_boot_drain_software_events(void) {
    TestEvent((*(s32 *)(&card_sw_done_event)));
    TestEvent((*(s32 *)(&card_sw_error_event)));
    TestEvent((*(s32 *)(&card_sw_timeout_event)));
    TestEvent((*(s32 *)(&card_sw_new_event)));
}
