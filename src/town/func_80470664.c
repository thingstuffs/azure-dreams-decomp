#include "common.h"

extern s32 func_8001628C();
extern s32 func_80017CC4();
extern s32 func_80017E98(s32, s32);
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 D_8001A9BC;
extern s32 D_8001B1FC;
extern s32 D_8001B63C;
extern s32 D_8001D270;

s32 func_80017664(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s1;

    if (func_80017E98(arg0, arg1) != 0) {
        return (s32)&D_8001B63C;
    }
    if (arg2 == 9) {
        func_80017CC4();
        var_s1 = func_80019ABC(&D_8001A9BC, &D_8001B1FC, arg0, 9);
        if (func_80019A04(&D_8001A9BC, arg0, 9) != 0) {
            var_s1 = func_8001628C(arg0, arg1, 9);
        }
    } else {
        var_s1 = (s32)&D_8001D270;
    }
    return var_s1;
}
