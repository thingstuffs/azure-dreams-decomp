#include "common.h"

extern s16 D_80018AEA;
extern s32 D_80018B00;
extern s32 D_80019A30;
extern s32 D_80019ACC;

extern void func_80017B3C(void *, s32);
extern s32 func_80017F8C(void *, s32, s32);
extern void func_80018854(s32);
extern s32 func_8001894C(s32);

void *func_80016444(s32 arg0, s32 unused, s32 arg2)
{
    void *base = &D_80018B00;

    func_80017B3C(base, arg0);
    if (((func_8001894C(D_80018AEA) == 0) &&
         (func_80017F8C(base, arg0, arg2) == 0)) ||
        (func_8001894C(0x50C) == 0)) {
        func_80018854(0x50C);
        return &D_80019ACC;
    }
    return &D_80019A30;
}
