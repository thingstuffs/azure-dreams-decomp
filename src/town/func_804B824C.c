#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800169F8();                            /* extern */
s32 func_80017F8C();         /* extern */
s32 func_80018044(); /* extern */
s32 func_8001894C();                             /* extern */
extern s16 D_80018AEA;
extern M2C_UNK D_80018B28;
extern M2C_UNK D_80018E38;

/* Runs the operation and invokes the fallback when both checks return zero. */
s32 func_80016A4C(s32 input, M2C_UNK unused, M2C_UNK aux_input) {
    s32 result;

    result = func_80018044(&D_80018B28, &D_80018E38, input, aux_input);
    if ((func_8001894C(D_80018AEA) == 0) && (func_80017F8C(&D_80018B28, input, aux_input) == 0)) {
        func_800169F8();
    }
    return result;
}
