#include "common.h"

extern u8 D_800181C8[];
extern u8 D_8001832C[];
extern u8 D_80019425[];
extern u8 D_80019915[];

extern void *func_80017674(void *, void *, void *, s32);
extern s32 func_800175BC(void *, void *, s32);
extern s32 func_80017F7C(s16);

/* Selects a result for the object, using its status to choose an override. */
void *func_800166C4(void *object, s32 unused, s32 mode)
{
    void *base;
    void *result;

    base = D_800181C8;
    result = func_80017674(base, D_8001832C, object, mode);
    if (func_800175BC(base, object, mode) != 0) {
        if (func_80017F7C(*(s16 *)((u8 *)object + 0x18)) != 0) {
            result = D_80019915;
        } else {
            result = D_80019425;
        }
    }
    return result;
}
