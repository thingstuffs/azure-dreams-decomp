#include "common.h"
#include "shared/record_ptrs.h"

#ifndef NULL
#define NULL 0
#endif


/* Return whether either object has the high state bit set and state code 5 through 7. */
s32 func_800A404C(void) {
    s32 index;
    s32 result;
    u16 state;
    void *object;
    void *base;

    index = 0;
    base = D_800814A8;
    do {
        object = *(void **)(base + 0xAC);
        if ((object != NULL) &&
            (state = *(u16 *)(object + 0x46), (state & 0x8000) != 0) &&
            ((u32)((state & 0x3FFF) - 5) < 3U)) {
            result = 1;
            return result;
        }

        index++;
        base += 4;
    } while (index < 2);

    result = 0;
    return result;
    result = 1;
    return result;
}
