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

/* Selects a result from the input checks and mode-specific lookups. */
s32 func_80017664(s32 input, s32 context, s32 mode) {
    s32 result;

    if (func_80017E98(input, context) != 0) {
        return (s32)&D_8001B63C;
    }
    if (mode == 9) {
        func_80017CC4();
        result = func_80019ABC(&D_8001A9BC, &D_8001B1FC, input, 9);
        if (func_80019A04(&D_8001A9BC, input, 9) != 0) {
            result = func_8001628C(input, context, 9);
        }
    } else {
        result = (s32)&D_8001D270;
    }
    return result;
}
