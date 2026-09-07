#include "common.h"

extern s32 func_80016BC0(void *, void *, s32, s32);
extern s32 func_80016B08(void *, s32, s32);
extern void func_80017674(s32);
extern s32 func_800176F4(s32);

extern u8 D_800178D8[];
extern u8 D_800179CC[];
extern u8 D_80018481[];
extern u8 D_80018642[];
extern u8 D_80018B70[];

s32 func_800160C8(s32 arg0, s32 unused, s32 arg2)
{
    s32 result;

    result = func_80016BC0(D_800178D8, D_800179CC, arg0, arg2);

    if (arg2 == 50 && func_80016B08(D_800178D8, arg0, 50)) {
        return (s32)D_80018481;
    }
    if (arg2 == 33 && func_80016B08(D_800178D8, arg0, 33)) {
        return (s32)D_80018642;
    }
    if (arg2 == 12) {
        if (!func_80016B08(D_800178D8, arg0, 12)) {
            func_80017674(0xB11);
        }
        if (func_800176F4(0xB11)) {
            return (s32)D_80018B70;
        }
    }
    return result;
}
