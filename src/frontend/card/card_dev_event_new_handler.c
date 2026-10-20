#include "common.h"

/* Set the word at 0x80409504 to 4 and return zero. */
s32 card_dev_event_new_handler(void) {
    *(s32 *)0x80409504 = 4;
    return 0;
}
