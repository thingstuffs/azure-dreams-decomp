#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

/* Latches the hardware I/O error event. */
s32 card_dev_event_error_handler(void) {
    card_dev_hardware_status = 2;
    return 0;
}
