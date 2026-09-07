#include "common.h"

extern s32 func_80033B2C(s32);
extern void func_80053DA8(s32);
extern void func_80094AF8(void);
extern s32 func_800AE324(s32);

s32 func_80094B0C(s32 arg0) {
    if (func_80033B2C(0xA5) != 0) {
        return 0;
    }
    func_80053DA8(0x514);
    func_80094AF8();
    return func_800AE324(arg0);
}
