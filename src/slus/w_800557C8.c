#include "common.h"

/* FIFO pop from u16 queue at D_80084778: [0]=count (clamped to 0x20),
 * [1..]=entries. Shifts remaining entries left and decrements count. */
extern u16 D_80084778[0x21];

/* Pops the oldest queue entry and shifts the rest left, returning zero if empty. */
u16 func_800557C8(void)
{
    u16 entry;
    u16 i;

    if (D_80084778[0] > 0x20) {
        D_80084778[0] = 0x20;
    }
    entry = 0;
    if (D_80084778[0] != 0) {
        entry = D_80084778[1];
        for (i = 1; i < D_80084778[0]; i++) {
            D_80084778[i] = D_80084778[i + 1];
        }
        D_80084778[0] = D_80084778[0] - 1;
    }
    return entry;
}
