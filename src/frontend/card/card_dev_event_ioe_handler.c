#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

/* Latches the hardware I/O completion event. */
s32 card_dev_event_ioe_handler(void) {
    card_dev_hardware_status = 1;
    return 0;
}
