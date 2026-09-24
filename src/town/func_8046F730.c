#include "common.h"

extern s32 func_8001628C();
extern s32 func_80017E98(s32, s32);
extern s32 func_80019880();
extern s32 func_80019A04();
extern s32 func_80019ABC();
extern s32 func_8001A7F8();
extern s32 D_8001A954;
extern s32 D_8001B1F8;
extern s32 D_8001B63C;
extern s32 D_800211DC;

/* Selects a response from the table, applying the threshold override and fallback. */
s32 func_80016730(s32 object, s32 check_value, s32 selection) {
    s32 response;

    if (func_80017E98(object, check_value) != 0) {
        return (s32)&D_8001B63C;
    }
    response = func_80019ABC(&D_8001A954, &D_8001B1F8, object, selection);
    if (func_8001A7F8() >= 10) {
        func_80019880();
        response = (s32)&D_800211DC;
    }
    if (func_80019A04(&D_8001A954, object, selection) != 0) {
        response = func_8001628C(object, check_value, selection);
    }
    return response;
}
