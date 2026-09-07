#include "common.h"

#include "common.h"

extern s32 func_8005DA88(s32 *arg0);
extern s8 D_8007382B[9];

s16 func_8005B378(s16 arg0)
{
    s32 sp10[6];

    sp10[0] = 1;
    sp10[1] = arg0;
    if (func_8005DA88(sp10) != 0) {
        return -1;
    }
    D_8007382B[0] = arg0;
    return arg0;
}
