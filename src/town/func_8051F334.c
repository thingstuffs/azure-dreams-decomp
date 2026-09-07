#include "common.h"

extern s32 func_80017D80();
extern void func_80018ADC();
extern s32 func_80018B5C();

s32 func_80016B34(void *arg0, s32 arg1) {
    s32 result;

    if (func_80018B5C(0x5C5) != 0) {
        func_80018ADC(0x5C5);
        func_80018ADC(0x5BF);
        func_80018ADC(0x5C0);
        func_80017D80(arg0, arg1);
        return 1;
    }

    if (func_80018B5C(*(s16 *)((u8 *)arg0 + 0x18)) == 0) {
        result = 0;
    } else {
        result = func_80017D80(arg0, arg1) ^ 1;
    }
    return result;
}
