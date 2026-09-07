#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800169F8();                            /* extern */
s32 func_80017F8C();         /* extern */
s32 func_80018044(); /* extern */
M2C_UNK func_80018854();                     /* extern */
s32 func_8001894C();                             /* extern */
extern s16 D_80018AEA;
extern M2C_UNK D_80018B38;
extern M2C_UNK D_80018E38;

s32 func_80016B84(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_s0;

    temp_s0 = func_80018044(&D_80018B38, &D_80018E38, arg0, arg2);
    if ((func_8001894C(D_80018AEA) == 0) && (func_80017F8C(&D_80018B38, arg0, arg2) == 0)) {
        func_800169F8();
    }
    func_80018854(0x1461);
    return temp_s0;
}
