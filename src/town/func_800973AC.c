#include "common.h"

extern s32 func_80033B2C(s32);
extern void SD_Call(s32);
extern void func_80094AF8(void);
extern s32 func_800AE324(s32);

/* Runs the action sequence for the context unless flag 0xA5 is set. */
s32 func_80094B0C(s32 context) {
    if (func_80033B2C(0xA5) != 0) {
        return 0;
    }
    SD_Call(0x514);
    func_80094AF8();
    return func_800AE324(context);
}
