#include "common.h"

extern s32 func_80019AB8(s32, s32);
extern void func_80019BC0(void);
extern s32 func_80019B54(s32, s32);
extern void func_8001AD60(s32);

s32 func_800184B8(s32 arg0, s32 arg1)
{
    if (func_80019AB8(13, 1) != 0) {
        func_80019BC0();
    }

    if (func_80019B54(arg0, arg1) == 0) {
        func_8001AD60(0xD7F);
        return 0;
    }

    return 1;
}
