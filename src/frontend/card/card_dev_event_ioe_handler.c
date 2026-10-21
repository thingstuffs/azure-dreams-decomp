#include "common.h"
#include "frontend/card.h"

/* Sets the flag at 0x80409504 and returns zero. */
s32 card_dev_event_ioe_handler(void) {
    *(s32 *)0x80409504 = 1;
    return 0;
}
