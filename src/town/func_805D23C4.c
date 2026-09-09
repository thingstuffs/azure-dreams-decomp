#include "common.h"

extern s32 D_80019AFC;
extern s32 func_8001628C(void);
extern s32 func_8001632C(s32, s32, s32, s32);

s32 func_800163C4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 state = D_80019AFC;

    if (state == 0) {
        return func_8001628C();
    }
    if (state == 2) {
        return func_8001632C(arg0, arg1, arg2, arg3);
    }
    return 0;
}
