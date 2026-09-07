#include "common.h"

extern s32 func_8001628C();
extern s32 func_80017E98();
extern s32 func_80019880();
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 D_8001A96C;
extern s32 D_8001B1F8;
extern s32 D_8001B63C;

s32 func_80016A3C(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s1;

    if (func_80017E98() != 0) {
        return (s32)&D_8001B63C;
    }
    var_s1 = func_80019ABC(&D_8001A96C, &D_8001B1F8, arg0, arg2);
    func_80019880();
    if (func_80019A04(&D_8001A96C, arg0, arg2) != 0) {
        var_s1 = func_8001628C(arg0, arg1, arg2);
    }
    return var_s1;
}
