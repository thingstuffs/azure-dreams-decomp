#include "common.h"

extern s8 D_80016000[];
extern s8 D_80018EBC[];
extern s32 D_800190B4;

extern void func_800182E4(void *, s32 *, s32, s32);
extern s32 func_80018D6C(s32);

void func_80016EFC(s32 arg0, s32 arg1, s32 arg2)
{
    s32 value;

    if (func_80018D6C(0xFCB) != 0) {
        value = 8;
    } else {
        value = ((*(s32 (**)(s32))((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x20) + 0x54))(4) & 3) * 2;
    }
    func_800182E4(D_80018EBC + (value * 8), &D_800190B4, arg0, arg2);
}
