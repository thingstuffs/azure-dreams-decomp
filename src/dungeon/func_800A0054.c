#include "common.h"

s32 func_800A57B4(void *arg0, s16 arg1) {
    s32 i;

    i = 0;
    do {
        u8 value = *((u8 *)arg0 + 8);

        if (value != 0 && (arg1 - 1) / 3 == (value - 1) / 3) {
            return (s16)i;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        i++;
        arg0 = (u8 *)arg0 + 3;
    } while (i < 3);
    return -1;
}
