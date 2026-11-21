#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

/* Latches the hardware timeout event. */
s32 card_dev_event_timeout_handler(void) {
    card_dev_hardware_status = 3;
    return 0;
}
