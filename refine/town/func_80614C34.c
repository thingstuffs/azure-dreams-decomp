#include "common.h"

extern s32 D_80018E1C;
extern s32 D_80018E34;
extern s32 D_8001925C;

extern void func_800181C8();
extern s32 func_80018C50();

/* Selects data using query 0xFBC and forwards it with the supplied values. */
void func_80016434(s32 primaryValue, s32 unusedValue, s32 secondaryValue) {
    register void *selectedData ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

    if (func_80018C50(0xFBC) != 0) {
        selectedData = &D_80018E34;
    } else {
        selectedData = &D_80018E1C;
    }
    func_800181C8(selectedData, &D_8001925C, primaryValue, secondaryValue);
}
