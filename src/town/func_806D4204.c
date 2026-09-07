#include "common.h"
#include "m2c_compat.h"

s32 func_80016D98();                         /* extern */
M2C_UNK func_80017960(); /* extern */
extern M2C_UNK D_800189A4;
extern M2C_UNK D_80018B94;

void func_806D4204(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (func_80016D98(arg2) == 0) {
        func_80017960(&D_800189A4, &D_80018B94, arg0, arg2);
    }
}
