#include "common.h"

extern int D_800814A0;

/* Decrements the counter and sets the preceding halfword and global flag bit 0x8000 if it remains nonzero. */
void func_8004B2E0(unsigned short *entry_data, int *counter)
{
    if (--(*counter) != 0) {
        entry_data[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
