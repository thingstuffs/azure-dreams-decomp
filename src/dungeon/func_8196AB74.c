#include "common.h"

extern s16 D_800269B4;
extern s32 D_800814A0;

/* Subtracts 8 from the object counter and sets flags when it reaches zero. */
void func_8196AB74(void *object)
{
    u8 *object_bytes = object;
    u16 counter;

    counter = *(u16 *)(object_bytes + 50);
    D_800269B4 = 1;
    counter -= 8;
    *(u16 *)(object_bytes + 50) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(object_bytes - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
