#include "modules/town_ovl_3ef1c8.h"

s32 func_80017100(s32 value, s32 check_value, s32 lookup_value) {
    s32 result;

    if (townCheckTableResultBelowMinus47(value, check_value) != 0) {
        return (s32)&D_8001B7AE;
    }
    result = func_80019ABC(&D_8001A994, &D_8001B1FC, value, lookup_value);
    if (func_80019A04(&D_8001A994, value, lookup_value) != 0) {
        result = (s32)&D_8001EDD0;
    }
    return result;
}
