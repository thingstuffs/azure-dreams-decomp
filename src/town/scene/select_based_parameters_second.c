#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

s32 func_800181C8(void *, void *, s32, s32);
s32 func_80018B58(s32);
s32 func_80018C50();
extern M2C_UNK D_80018EF4;
extern M2C_UNK D_80018F0C;
extern M2C_UNK D_8001925C;

/* Selects data based on the 0xFB1 check and forwards it with the caller's parameters. */
void select_based_parameters(s32 callerValue, s32 unused, s32 callerData) {

    func_80018B58(Ft_nyu);
    if (func_80018C50(Fr_hospital_naoruru) == 0) {
        func_800181C8(&D_80018EF4, &D_8001925C, callerValue, callerData);
    } else {
        func_800181C8(&D_80018F0C, &D_8001925C, callerValue, callerData);
    }
}
