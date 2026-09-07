#include "common.h"

extern s32 func_8001A510(s32 arg0);
extern void func_8001A418(s32 arg0);
extern void func_8001A490(s32 arg0);

s32 func_8046F224(s32 arg0, s32 arg1) {
    if (func_8001A510(arg0) == 0) {
        return 1;
    }
    if (func_8001A510(0x7A3) != 0) {
        return 1;
    }
    func_8001A418(0x7A3);
    func_8001A418(arg1);
    func_8001A490(arg0);
    return 0;
}
