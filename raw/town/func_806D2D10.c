#include "common.h"

extern void func_80016CCC();
extern void func_80016D20();
extern s32 func_80016D78();

void func_80016510(s16 arg0, s16 arg1) {
    if (func_80016D78(arg0) != 0) {
        func_80016CCC(arg1);
    } else {
        func_80016D20(arg1);
    }
    func_80016CCC(arg0);
}
