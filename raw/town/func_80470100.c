#include "common.h"

extern s32 func_80017E98(s32, s32);
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 D_8001A994;
extern s32 D_8001B1FC;
extern s32 D_8001B7AE;
extern s32 D_8001EDD0;

/* Select a lookup result or a fixed address according to the two checks. */
s32 func_80470100(s32 value, s32 check_value, s32 lookup_value) {
    s32 result;

    if (func_80017E98(value, check_value) != 0) {
        return (s32)&D_8001B7AE;
    }
    result = func_80019ABC(&D_8001A994, &D_8001B1FC, value, lookup_value);
    if (func_80019A04(&D_8001A994, value, lookup_value) != 0) {
        result = (s32)&D_8001EDD0;
    }
    return result;
}
