#include "common.h"

extern s32 func_8001628C();
extern s32 func_80017E98(s32, s32);
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 D_8001A93C;
extern s32 D_8001B1F8;
extern s32 D_8001B63C;

/* Select a table result, using an override or fallback when its check succeeds. */
s32 func_8046F4A0(s32 context, s32 check_value, s32 selector) {
    s32 result;

    if (func_80017E98(context, check_value) != 0) {
        return (s32)&D_8001B63C;
    }
    result = func_80019ABC(&D_8001A93C, &D_8001B1F8, context, selector);
    if (func_80019A04(&D_8001A93C, context, selector) != 0) {
        result = func_8001628C(context, check_value, selector);
    }
    return result;
}
