#include "common.h"

typedef s32 M2C_UNK;

extern void *func_8001628C();
extern s32 func_80017E98(s32, s32);
extern M2C_UNK func_80019880(void);
extern s32 func_80019A04();
extern M2C_UNK *func_80019ABC();
extern s32 func_8001A7F8();

extern M2C_UNK D_8001A94C;
extern s32 D_8001B1F8;
extern s32 D_8001B63C;
extern M2C_UNK D_80020E5C;

/* Selects a lookup result or a fallback based on the input checks. */
void *func_80016640(s32 selector, s32 check_value, s32 lookup_value) {
    void *result;

    if (func_80017E98(selector, check_value) != 0) {
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
