#include "common.h"

/* Returns whether the value at 0x804094EC is nonzero. */
s32 card_dev_has_selected_channel(void) {
    return *(s32 *)0x804094EC != 0;
}
