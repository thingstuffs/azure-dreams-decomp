#include "modules/main_server_ship.h"
#include "common.h"
#include "main.h"
#include "sdk/libapi.h"

/* Clear the event status and test the four event handles. */
void card_boot_drain_hardware_events(void) {
    (*(s32 *)(&card_hardware_status)) = 0;
    TestEvent((*(s32 *)(&card_hw_done_event)));
    TestEvent((*(s32 *)(&card_hw_error_event)));
    TestEvent((*(s32 *)(&card_hw_timeout_event)));
    TestEvent((*(s32 *)(&card_hw_new_event)));
}
