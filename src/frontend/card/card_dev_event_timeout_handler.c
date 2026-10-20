#include "common.h"

/* Set the value at 0x80409504 to 3 and return zero. */
s32 card_dev_event_timeout_handler(void) {
    *(s32 *)0x80409504 = 3;
    return 0;
}
