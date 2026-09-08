#include "common.h"

extern s32 func_8004D0C8(s32);
extern s32 D_80100D90;

void func_800A48F8(s32 arg0) {
    func_8004D0C8(arg0);
    D_80100D90 = arg0;
}
