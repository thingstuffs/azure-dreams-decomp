#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "main/data.h"

/* Pass each of the four stored values to the shared callback. */
void card_dev_drain_hw_events(void) {
    TestEvent_8007C9C8(dev_card_sw_done_event);
    TestEvent_8007C9C8(dev_card_sw_error_event);
    TestEvent_8007C9C8(dev_card_sw_timeout_event);
    TestEvent_8007C9C8(dev_card_sw_new_event);
}
