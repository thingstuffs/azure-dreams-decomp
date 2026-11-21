#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "main/data.h"


/* Clears the state flag and processes the four stored handles. */
void card_dev_drain_sw_events(void) {
    card_dev_hardware_status = 0;
    TestEvent_8007C9C8(dev_card_hw_done_event);
    TestEvent_8007C9C8(dev_card_hw_error_event);
    TestEvent_8007C9C8(dev_card_hw_timeout_event);
    TestEvent_8007C9C8(dev_card_hw_new_event);
}
