#include "common.h"

extern s32 func_800187FC(void);
extern s32 func_800178D0(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80017978();

void func_800167DC(s32 arg0, s32 arg1, s32 arg2) {
    /* MATCH: func_800187FC preserves the incoming argument registers. */
    register s32 pass0 ASM_REG("$4") = arg0;
    register s32 pass1 ASM_REG("$5") = arg1;
    register s32 pass2 ASM_REG("$6") = arg2;
    if (func_800187FC() >= 40) {
        func_800178D0(pass0, pass1, pass2);
    }
    func_80017978(arg0, arg1);
}
