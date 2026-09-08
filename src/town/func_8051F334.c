#include "common.h"

extern s32 func_80017D80();
extern void func_80018ADC();
extern s32 func_80018B5C();

/* Checks the entry and override flags before calling the handler. */
s32 func_80016B34(void *entry, s32 handler_arg) {
    s32 result;

    if (func_80018B5C(0x5C5) != 0) {
        func_80018ADC(0x5C5);
        func_80018ADC(0x5BF);
        func_80018ADC(0x5C0);
        func_80017D80(entry, handler_arg);
        return 1;
    }

    if (func_80018B5C(*(s16 *)((u8 *)entry + 0x18)) == 0) {
        result = 0;
    } else {
        result = func_80017D80(entry, handler_arg) ^ 1;
    }
    return result;
}
