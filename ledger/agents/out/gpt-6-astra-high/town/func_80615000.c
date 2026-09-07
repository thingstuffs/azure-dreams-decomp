#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800181C8();
M2C_UNK func_80018B58();
s32 func_80018C50();
extern M2C_UNK D_80018EF4;
extern M2C_UNK D_80018F0C;
extern M2C_UNK D_8001925C;

/* Selects data based on the 0xFB1 check and forwards it with the caller's parameters. */
void func_80016800(s32 callerValue, s32 unused, M2C_UNK callerData) {
    register void *selectedData ASM_REG("$4");   /* MATCH pin: retail immediate-load split depends on it */

    func_80018B58(0xFE2);
    if (func_80018C50(0xFB1) == 0) {
        selectedData = &D_80018EF4;
    } else {
        selectedData = &D_80018F0C;
    }
    func_800181C8(selectedData, &D_8001925C, callerValue, callerData);
}
