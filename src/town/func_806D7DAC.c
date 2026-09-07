#include "common.h"

extern s32 func_80017B0C(void *, void *, s32, s32);
extern s32 func_80017A54(void *, s32, s32);
extern void func_800185C0(s32);

extern u8 D_800189D8[];
extern u8 D_80019104[];
extern u8 D_8001A212[];
extern u8 D_8001ABCC[];
extern u8 D_80019397[];

s32 func_800165AC(s32 arg0, s32 unused, s32 arg2)
{
    s32 result;

    result = func_80017B0C(D_800189D8, D_80019104, arg0, arg2);

    if (arg2 == 45 && func_80017A54(D_800189D8, arg0, 45)) {
        func_800185C0(0x9AE);
        return (s32)D_8001A212;
    }
    if (arg2 == 46 && func_80017A54(D_800189D8, arg0, 46)) {
        return (s32)D_8001ABCC;
    }
    if (arg2 == 47 && func_80017A54(D_800189D8, arg0, 47)) {
        return (s32)D_80019397;
    }
    return result;
}
