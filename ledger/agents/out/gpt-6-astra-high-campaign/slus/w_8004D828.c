#include "common.h"

extern u16 D_8007142C[];
extern u8 D_8007147C[];

/* Returns the byte mapped to the low 16 bits of key, or the zero-terminator entry if absent. */
u8 func_8004D828(s32 key)
{
    u16 first_key;
    s32 key_index;

    key_index = 0;
    first_key = D_8007142C[0];
    if (first_key != 0) {
        while (D_8007142C[key_index] != (key & 0xFFFF)) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            key_index++;
            if (D_8007142C[key_index] == 0) {
                break;
            }
        }
    }
    return D_8007147C[key_index];
}
