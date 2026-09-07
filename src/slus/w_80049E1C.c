#include "common.h"

s32 func_80049E1C(s32 arg0, s32 arg1, s32 arg2)
{
    s32 ret;
    s32 temp;

    ret = arg0;
    if (arg2 != 0) {
        ret += arg1;
        if (arg1 >= 0) {
            arg0 = ret;
            arg2 -= 1;
            if (arg0 >= arg2) {
                arg0 = arg2;
            }
            ret = arg0;
        } else {
            temp = ret;
            if (ret < 0) {
                temp = 0;
            }
            ret = temp;
        }
    } else {
        ret = 0;
    }

    return ret;
}
