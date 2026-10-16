#include "common.h"

extern int D_800814A0;

/* Decrements the counter and sets the preceding halfword and global flag bit 0x8000 if it remains nonzero. */
void tableHandleDecrementsCounterSetsPrecedingHalfwordGlobalFlagBitHex8000Remains(unsigned short *entry_data, int *counter)
{
    unsigned short *flags = entry_data - 1;

    if (--(*counter) != 0) {
        *flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
