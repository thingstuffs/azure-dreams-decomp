#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void *D_800814A8;

s32 func_800A404C(void) {
    s32 index;
    s32 result;
    u16 state;
    void *object;
    void *base;

    index = 0;
    base = D_800814A8;
loop:
    object = *(void **)(base + 0xAC);
    if ((object != NULL) &&
        (state = *(u16 *)(object + 0x46), (state & 0x8000) != 0) &&
        ((u32)((state & 0x3FFF) - 5) < 3U)) {
        goto success;
    }

    index++;
    base += 4;
    if (index < 2) {
        goto loop;
    }

    result = 0;
    goto done;
success:
    result = 1;
done:
    ASM_KEEP(result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    return result;
}
