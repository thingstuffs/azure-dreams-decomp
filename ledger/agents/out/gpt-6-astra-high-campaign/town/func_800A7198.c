#include "common.h"

extern s32 func_8004D0C8(s32);
extern s32 D_80100D90;

/* Apply the setting and store its current value. */
void func_800A48F8(s32 setting) {
    func_8004D0C8(setting);
    D_80100D90 = setting;
}
