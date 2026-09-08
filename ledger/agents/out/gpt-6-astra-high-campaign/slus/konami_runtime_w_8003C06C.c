#include "common.h"

#include "common.h"

extern unsigned char D_80082E6A[9];

extern u32 D_8006B008[3];
extern u32 D_800D0858[3];

/* Returns an indexed value from the table selected by the current mode. */
u32 func_8003C06C(s32 index)
{
    if (D_80082E6A[0] == 2) {
        return D_8006B008[index];
    }

    return D_800D0858[index];
}
