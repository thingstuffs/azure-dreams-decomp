#include "common.h"

typedef s32 M2C_UNK;

M2C_UNK func_80017B84();
M2C_UNK func_80018ADC();
s32 func_80018B5C();
#ifdef NON_MATCHING
extern void func_800165E8(s32 arg0) __attribute__((noreturn));
#endif

#ifndef NON_MATCHING
s32 func_8051EDA4(s32 arg0, M2C_UNK arg1) {
    s32 result;

    func_80018ADC(0x5BC);
    if (func_80018B5C(0x9A) == 0) {
        result = 0;
        goto done;
    } else {
        func_80017B84(arg0, arg1);
        result = 1;
        goto done;
    }

done:
    return result;
}
#else
s32 func_8051EDA4(s32 arg0, M2C_UNK arg1) {
    func_80018ADC(0x5BC);
    if (func_80018B5C(0x9A) == 0) {
        func_800165E8(arg0);
    }
    func_80017B84(arg0, arg1);
    return 1;
}
#endif
