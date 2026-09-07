#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_8009EB3C();
extern s32 func_8009F6E4();

s32 func_8009EB9C(s32 arg0) {
    s32 ret;

    ret = func_8009F6E4();
    if (ret == -1) {
        return 0;
    }
    func_8009EB3C(arg0, ret);
    return 1;
}
