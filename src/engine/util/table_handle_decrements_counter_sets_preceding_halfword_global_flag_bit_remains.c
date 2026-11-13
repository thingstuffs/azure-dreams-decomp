#include "common.h"
#include "shared/object_flags.h"
#include "engine/util.h"

extern int D_800814A0;

/* Decrements the counter and sets the preceding halfword and global flag bit 0x8000 if it remains nonzero. */
void decrement_and_flag_removal_if_nonzero(unsigned short *entry_data, int *counter)
{
    unsigned short *flags = entry_data - 1;

    if (--(*counter) != 0) {
        *flags |= 0x8000;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}
