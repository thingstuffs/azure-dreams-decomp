#include "common.h"

extern s32 func_8001628C();
extern s32 func_80017E98(s32, s32);
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 D_8001A9C4;
extern s32 D_8001B1FC;
extern s32 D_8001B63C;

/* Select a table result, using an override or fallback when its check succeeds. */
s32 func_80470758(s32 context, s32 check_value, s32 selector) {
    s32 result;

    if (func_80017E98(context, check_value) != 0) {
        return (s32)&D_8001B63C;
    }
    result = func_80019ABC(&D_8001A9C4, &D_8001B1FC, context, selector);
    if (func_80019A04(&D_8001A9C4, context, selector) != 0) {
        result = func_8001628C(context, check_value, selector);
    }
    return result;
}
