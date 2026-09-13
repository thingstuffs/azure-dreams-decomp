#include "common.h"

typedef s32 M2C_UNK;

M2C_UNK func_80017B84();
M2C_UNK func_80018ADC();
s32 func_80018B5C();
#ifndef NON_MATCHING
extern void func_800165E8(void) __attribute__((noreturn));
#else
extern void func_800165E8(s32 arg0) __attribute__((noreturn));
#endif

#ifndef NON_MATCHING
register s16 dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
s32 dispatch_arg;
#endif

s32 func_8051EDA4(s32 arg0, M2C_UNK arg1) {
    func_80018ADC(0x5BC);
#ifndef NON_MATCHING
    if (func_80018B5C(0x9A) == 0) {
        dispatch_result = 0;
        func_800165E8();
        dispatch_arg = arg0;
    }
#else
    if (func_80018B5C(0x9A) == 0) {
        func_800165E8(arg0);
    }
#endif
    func_80017B84(arg0, arg1);
    return 1;
}
