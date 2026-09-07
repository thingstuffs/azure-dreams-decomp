#include "common.h"

extern s32 D_80018DFC;
extern s32 D_800190B4;

extern s32 func_800182E4(s32 *, s32 *, s32, s32);
extern void func_80018C74(s32);
extern s32 func_80018D6C(s32);

s32 func_800166CC(s32 arg0, s32 arg1, s32 arg2)
{
    func_80018C74(0x1463);
    if ((func_80018D6C(0xFDA) == 0) &&
        (func_80018D6C(0xFDB) == 0)) {
        return 0;
    }
    return func_800182E4(&D_80018DFC, &D_800190B4, arg0, arg2);
}
