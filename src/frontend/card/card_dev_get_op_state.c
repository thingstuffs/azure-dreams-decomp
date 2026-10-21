#include "common.h"
#include "frontend/card.h"

/* Returns the signed 32-bit value stored at 0x804094E8. */
s32 card_dev_get_op_state(void) {
    return *(s32 *)0x804094E8;
}
