#include "common.h"

extern void func_80017BA0(s32, s32);
extern void func_80018854(s32 arg0);
extern s32 func_8001894C(s32 arg0);

extern u8 D_80019950[];
extern u8 D_80019A10[];

void *func_80016D78(s32 arg0, s32 arg1) {
    void *result;

    func_80017BA0(arg0, arg1);
    if (func_8001894C(0x507) != 0) {
        goto nonzero;
    }
    func_80018854(0x507);
    result = D_80019950;
    goto done;

nonzero:
    result = D_80019A10;

done:
    return result;
}
