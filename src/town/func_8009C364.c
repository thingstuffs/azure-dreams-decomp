#include "common.h"

extern void townInitializePlayerDataReference(void *);

/* Decrement the object countdown and call its handler when it becomes negative. */
void townTickPlayerCountdown(void *object)
{
    u16 countdown;

    countdown = *(u16 *)((u8 *)object + 0xA) - 1;
    *(u16 *)((u8 *)object + 0xA) = countdown;
    if ((s16)countdown < 0) {
        townInitializePlayerDataReference(object);
    }
}
