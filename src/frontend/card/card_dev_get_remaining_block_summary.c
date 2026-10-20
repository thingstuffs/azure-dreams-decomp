#include "common.h"

extern s32 D_8009EB54[4];

/* Returns the second or third table entry based on the flag at 0x804094EC. */
s32 card_dev_get_remaining_block_summary(void) {
    s32 *entry = &D_8009EB54[1];

    if (*(s32 *)0x804094EC != 0) {
        entry++;
    }
    return *entry;
}
