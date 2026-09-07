#include "common.h"

extern s32 func_80017B0C(void *, void *, s32, s32);
extern s32 func_80017A54(void *, s32, s32);

extern u8 D_80018998[];
extern u8 D_80019104[];
extern u8 D_80019AB6[];
extern u8 D_8001ABCC[];
extern u8 D_80019397[];

s32 func_80016334(s32 arg0, s32 unused, s32 arg2)
{
    s32 result;

    result = func_80017B0C(D_80018998, D_80019104, arg0, arg2);

    if (arg2 == 45 && func_80017A54(D_80018998, arg0, 45)) {
        return (s32)D_80019AB6;
    }
    if (arg2 == 46 && func_80017A54(D_80018998, arg0, 46)) {
        return (s32)D_8001ABCC;
    }
    if (arg2 == 47 && func_80017A54(D_80018998, arg0, 47)) {
        return (s32)D_80019397;
    }
    return result;
}
