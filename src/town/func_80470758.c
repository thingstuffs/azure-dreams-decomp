#include "modules/town_ovl_3ef1c8.h"

s32 func_80017758(s32 context, s32 check_value, s32 selector) {
    s32 result;

    if (townCheckTableResultBelowMinus47(context, check_value) != 0) {
        return (s32)&D_8001B63C;
    }
    result = func_80019ABC(&D_8001A9C4, &D_8001B1FC, context, selector);
    if (func_80019A04(&D_8001A9C4, context, selector) != 0) {
        result = func_8001628C(context, check_value, selector);
    }
    return result;
}
