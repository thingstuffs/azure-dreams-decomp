#include "common.h"

extern s32 func_8001A4F0(void);
extern s32 func_8001A58C(s32, s32, s32, s32);

s32 func_8001BC60(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (func_8001A58C(arg0, arg1, arg2, arg3) != 0) {
        return arg0;
    }
    return func_8001A4F0();
}
