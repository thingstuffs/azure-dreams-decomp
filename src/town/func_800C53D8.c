#include "common.h"

extern s32 func_800C2AE8(void *);

s32 func_800C2B38(void *arg0) {
    s32 result;

    result = func_800C2AE8(arg0);
    if ((result << 16) > 0) {
        result = 0;
    }
    return (result << 16) >> 16;
}
