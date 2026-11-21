#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

/* Latches the hardware new-card event. */
s32 card_dev_event_new_handler(void) {
    card_dev_hardware_status = 4;
    return 0;
}
