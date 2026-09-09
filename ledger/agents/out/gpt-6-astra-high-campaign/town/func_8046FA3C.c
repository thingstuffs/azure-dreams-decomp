#include "common.h"

extern s32 func_8001628C();
extern s32 func_80017E98(s32, s32);
extern s32 func_80019880();
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 D_8001A96C;
extern s32 D_8001B1F8;
extern s32 D_8001B63C;

/* Check the input and return the primary or fallback result. */
s32 func_80016A3C(s32 input, s32 check_value, s32 context) {
    s32 result;

    if (func_80017E98(input, check_value) != 0) {
        return (s32)&D_8001B63C;
    }
    result = func_80019ABC(&D_8001A96C, &D_8001B1F8, input, context);
    func_80019880();
    if (func_80019A04(&D_8001A96C, input, context) != 0) {
        result = func_8001628C(input, check_value, context);
    }
    return result;
}
