#include "common.h"
#include "shared/object_flags.h"

extern s16 D_800266BC;

/* Decrement the record counter and set completion flags when it reaches zero. */
void func_80025348(void *record)
{
    u8 *record_bytes = record;
    u16 counter;

    counter = *(u16 *)(record_bytes + 2);
    D_800266BC = 1;
    counter--;
    *(u16 *)(record_bytes + 2) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(record_bytes - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

