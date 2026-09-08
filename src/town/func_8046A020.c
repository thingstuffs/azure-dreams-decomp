#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80019730(s32, s32);
extern M2C_UNK D_8001601C;
extern u8 D_80017774[];
extern M2C_UNK D_8002576F;

M2C_UNK *func_8001B020(s32 arg0, s32 arg1, s32 arg2) {
    M2C_UNK *ret;

    if (arg2 == 5) {
        ret = (M2C_UNK *)D_80017774;
        goto done;
    }
    if (arg2 == 4) {
        goto case_4;
    }
    func_80019730(arg0, arg1);
    ret = &D_8002576F;
    goto done;

case_4:
    ret = &D_8001601C;

done:
    return ret;
}
