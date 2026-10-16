#include "modules/town_ovl_3ef1c8.h"

s32 townSelectModeNineLookup(s32 input, s32 context, s32 mode) {
    s32 result;

    if (townCheckTableResultBelowMinus47(input, context) != 0) {
        return (s32)&D_8001B63C;
    }
    if (mode == 9) {
        townInvokeHandlerWithCode1470();
        result = func_80019ABC(&D_8001A9BC, &D_8001B1FC, input, 9);
        if (func_80019A04(&D_8001A9BC, input, 9) != 0) {
            result = func_8001628C(input, context, 9);
        }
    } else {
        result = (s32)&D_8001D270;
    }
    return result;
}
