#include "common.h"

#include "common.h"

extern unsigned char D_80082E6A[9];

extern u32 D_8006B008[3];
extern u32 D_800D0858[3];

u32 func_8003C06C(s32 arg0)
{
    if (D_80082E6A[0] == 2) {
        return D_8006B008[arg0];
    }

    return D_800D0858[arg0];
}
