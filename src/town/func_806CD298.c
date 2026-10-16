#include "modules/town_ovl_64d298.h"

/* Runs the threshold handler when the queried value reaches 30, then forwards the arguments. */
void func_80016298(s32 value, s32 context) {
    if (func_800175D0() >= 30) {
        func_80016A1C();
    }
    func_80016AC4(value, context);
}
