#include "common.h"

extern u16 D_8007142C[];
extern u8 D_8007147C[];

/* Returns the byte mapped to the low 16 bits of key, or the zero-terminator entry if absent. */
u8 func_8004D828(s32 key)
{
    s32 key_index;

    key_index = 0;
    while (D_8007142C[key_index] != 0) {
        if (D_8007142C[key_index] == (u16)key) {
            break;
        }
        key_index++;
    }
    return D_8007147C[key_index];
}
