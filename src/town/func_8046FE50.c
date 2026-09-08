#include "common.h"

extern s32 func_80017E98(s32, s32);
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 D_8001A984;
extern s32 D_8001B1FC;
extern s32 D_8001B6D0;
extern s32 D_8001F560;

s32 func_80016E50(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s1;

    if (func_80017E98(arg0, arg1) != 0) {
        return (s32)&D_8001B6D0;
    }
    var_s1 = func_80019ABC(&D_8001A984, &D_8001B1FC, arg0, arg2);
    if (func_80019A04(&D_8001A984, arg0, arg2) != 0) {
        var_s1 = (s32)&D_8001F560;
    }
    return var_s1;
}
