#include "common.h"

extern s32 func_8004D0C8();
extern s32 D_80100D90;

void func_800A48F8(s32 arg0) {
    func_8004D0C8();
    D_80100D90 = arg0;
}
