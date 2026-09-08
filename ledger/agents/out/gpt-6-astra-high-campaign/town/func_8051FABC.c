#include "common.h"

extern s32 func_80018A64();
extern s32 func_80018ADC();
extern s32 func_80018B5C();

/* Updates flag 0x5C4 to reflect flag 0x5C3 and returns its state. */
s32 func_800172BC(void) {
    if (func_80018B5C(0x5C3) != 0) {
        func_80018A64(0x5C4);
        return 1;
    }

    func_80018ADC(0x5C4);
    return 0;
}
