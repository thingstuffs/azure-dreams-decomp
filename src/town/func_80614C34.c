#include "common.h"

extern s32 D_80018E1C;
extern s32 D_80018E34;
extern s32 D_8001925C;

extern void func_800181C8();
extern s32 func_80018C50();

/* Selects data using query 0xFBC and forwards it with the supplied values. */
void func_80016434(s32 primaryValue, s32 unusedValue, s32 secondaryValue) {

    if (func_80018C50(0xFBC) != 0) {
        func_800181C8(&D_80018E34, &D_8001925C, primaryValue, secondaryValue);
    } else {
        func_800181C8(&D_80018E1C, &D_8001925C, primaryValue, secondaryValue);
    }
}
