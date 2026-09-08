#include "common.h"

extern s32 func_800175D0(void);
extern s32 func_80016A1C();
extern s32 func_80016AC4();

/* Runs the threshold handler when the queried value reaches 30, then forwards the arguments. */
void func_806CD298(s32 value, s32 context) {
    if (func_800175D0() >= 30) {
        func_80016A1C();
    }
    func_80016AC4(value, context);
}
