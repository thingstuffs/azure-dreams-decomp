#include "common.h"

typedef s32 M2C_UNK;

extern s32 func_8001628C();
extern s32 func_80017E98(s32, M2C_UNK);
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern M2C_UNK D_8001A934;
extern M2C_UNK D_8001B1F8;
extern M2C_UNK D_8001B63C;

/* Select a table result, using an override or fallback when its check succeeds. */
s32 func_800163D0(s32 context, M2C_UNK check_value, M2C_UNK selector) {
    s32 result;

    if (func_80017E98(context, check_value) != 0) {
        return (s32)&D_8001B63C;
    }
    result = func_80019ABC(&D_8001A934, &D_8001B1F8, context, selector);
    if (func_80019A04(&D_8001A934, context, selector) != 0) {
        result = func_8001628C(context, check_value, selector);
    }
    return result;
}
