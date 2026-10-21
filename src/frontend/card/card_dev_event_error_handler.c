#include "common.h"
#include "frontend/card.h"

/* Sets the value at 0x80409504 to 2 and returns zero. */
s32 card_dev_event_error_handler(void) {
    *(s32 *)0x80409504 = 2;
    return 0;
}
