#include "common.h"

extern s32 func_80019618();
extern s32 func_80019814();
extern s32 func_80019880();
extern s32 func_8001A510();

s32 func_80017098(s32 arg0, s32 arg1) {
    s32 result;

    if (func_8001A510(0x798) != 0) {
        s32 call_arg = arg0;

        
        func_80019880();
        result = func_80019814(arg0, arg1);
    } else {
        func_80019618(arg0, arg1);
        result = 1;
    }

    return result;
}
