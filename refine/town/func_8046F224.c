#include "common.h"

extern s32 func_8001A510(s32 arg0);
extern void func_8001A418(s32 arg0);
extern void func_8001A490(s32 arg0);

// Consume the required flag and set the completion flags if flag 0x7A3 is clear.
s32 func_8046F224(s32 requiredFlag, s32 completionFlag) {
    if (func_8001A510(requiredFlag) == 0) {
        return 1;
    }
    if (func_8001A510(0x7A3) != 0) {
        return 1;
    }
    func_8001A418(0x7A3);
    func_8001A418(completionFlag);
    func_8001A490(requiredFlag);
    return 0;
}
