#include "modules/town_ovl_3ef1c8.h"

void *townSelectLookupWithProgressThreshold(s32 selector, s32 check_value, s32 lookup_value) {
    void *result;

    if (townCheckTableResultBelowMinus47(selector, check_value) != 0) {
        return &D_8001B63C;
    }
    result = func_80019ABC(&D_8001A94C, &D_8001B1F8, selector, lookup_value);
    if (func_8001A7F8() >= 5) {
        func_80019880();
        result = &D_80020E5C;
    }
    if (func_80019A04(&D_8001A94C, selector, lookup_value) != 0) {
        result = func_8001628C(selector, check_value, lookup_value);
    }
    return result;
}
