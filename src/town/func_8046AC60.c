#include "common.h"

extern s32 func_8001A4F0(void);
extern s32 func_8001A58C(void);

s32 func_8001BC60(s32 arg0) {
    if (func_8001A58C() != 0) {
        return arg0;
    }
    return func_8001A4F0();
}
