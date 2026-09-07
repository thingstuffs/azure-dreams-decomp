#include "common.h"

extern u8 D_80017A18[9];
extern u8 D_80017B5C[9];
extern u8 D_80018AE5[9];

extern void *func_80016F14(void *, void *, void *, s32);
extern s32 func_80016EB8(void *, void *, s32);
extern s32 func_8001781C(s16);

void *func_80761B70(void *arg0, s32 arg1, s32 arg2)
{
    void *result;

    result = func_80016F14(D_80017A18, D_80017B5C, arg0, arg2);
    if (func_80016EB8(D_80017A18, arg0, arg2) != 0) {
        if (func_8001781C(*(s16 *)((u8 *)arg0 + 0x18)) != 0) {
            result = D_80018AE5;
        }
    }
    return result;
}
