#include "common.h"

extern u8 D_800181C8[];
extern u8 D_8001832C[];
extern u8 D_80019425[];
extern u8 D_80019915[];

extern void *func_80017674(void *, void *, void *, s32);
extern s32 func_800175BC(void *, void *, s32);
extern s32 func_80017F7C(s16);

void *func_800166C4(void *arg0, s32 arg1, s32 arg2)
{
    void *base;
    void *result;

    base = D_800181C8;
    result = func_80017674(base, D_8001832C, arg0, arg2);
    if (func_800175BC(base, arg0, arg2) != 0) {
        if (func_80017F7C(*(s16 *)((u8 *)arg0 + 0x18)) != 0) {
            result = D_80019915;
        } else {
            result = D_80019425;
        }
    }
    return result;
}
