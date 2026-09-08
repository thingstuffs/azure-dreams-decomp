#include "common.h"

extern s32 D_80028550[];
extern s32 D_80028554[];
extern s32 D_80028558[];
extern s32 D_8002855C[];

extern s32 func_8006A024();
/* Returns the first slot (1-4) whose value passes func_8006A024, or zero. */
s32 func_80021410(void)
{
    s32 matching_slot = 0;

    if (func_8006A024(D_80028550[0]) != 0) {
        matching_slot = 1;
        goto done;
    }
    if (func_8006A024(D_80028554[0]) != 0) {
        matching_slot = 2;
        goto done;
    }
    if (func_8006A024(D_80028558[0]) != 0) {
        matching_slot = 3;
        goto done;
    }
    if (func_8006A024(D_8002855C[0]) != 0) {
        matching_slot = 4;
    }
done:
    return matching_slot;
}
