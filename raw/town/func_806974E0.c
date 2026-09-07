#include "common.h"

extern s32 func_8001689C();

s32 func_806974E0(s32 arg0) {
    if (func_8001689C() == 0) {
        return 0;
    }
    return func_8001689C(arg0);
}
