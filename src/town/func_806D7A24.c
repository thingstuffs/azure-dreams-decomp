#include "common.h"

extern u8 D_80018980[];
extern u8 D_80019104[];
extern u8 D_80019397[];
extern u8 D_800197D0[];

extern void *func_80017B0C(void *, void *, s32, s32);
extern s32 func_80017A54(void *, s32, s32);

void *func_80016224(s32 arg0, s32 arg1, s32 arg2)
{
    void *result;

    result = func_80017B0C(D_80018980, D_80019104, arg0, arg2);
    if (arg2 == 0x2D && func_80017A54(D_80018980, arg0, 0x2D) != 0) {
        return D_800197D0;
    }
    if (arg2 == 0x2F && func_80017A54(D_80018980, arg0, 0x2F) != 0) {
        return D_80019397;
    }
    return result;
}
