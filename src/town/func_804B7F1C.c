#include "common.h"

extern void func_8001611C(s32, s32);
extern s32 func_8001894C(s32);
extern s32 func_80017D9C(s32, s32);

s32 func_8001671C(s32 arg0, s32 arg1) {
    s32 result;

    func_8001611C(arg0, arg1);
    if (func_8001894C(0x50F) != 0) {
        result = func_80017D9C(arg0, arg1);
    } else {
        result = 0;
    }
    return result;
}
