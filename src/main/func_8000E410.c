#include "common.h"

extern s32 D_80028550[];
extern s32 D_80028554[];
extern s32 D_80028558[];
extern s32 D_8002855C[];

extern s32 func_8006A024();
s32 func_80021410(void)
{
    s32 result = 0;

    if (func_8006A024(D_80028550[0]) != 0) {
        result = 1;
        goto done;
    }
    if (func_8006A024(D_80028554[0]) != 0) {
        result = 2;
        goto done;
    }
    if (func_8006A024(D_80028558[0]) != 0) {
        result = 3;
        goto done;
    }
    if (func_8006A024(D_8002855C[0]) != 0) {
        result = 4;
    }
done:
    return result;
}
