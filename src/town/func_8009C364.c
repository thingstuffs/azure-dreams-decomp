#include "common.h"

extern void func_8009A18C(void *);

/* Decrement the object countdown and call its handler when it becomes negative. */
void func_80099AC4(void *object)
{
    u16 countdown;

    countdown = *(u16 *)((u8 *)object + 0xA) - 1;
    *(u16 *)((u8 *)object + 0xA) = countdown;
    if ((s16)countdown < 0) {
        func_8009A18C(object);
    }
}
