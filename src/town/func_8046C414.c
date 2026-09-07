#include "common.h"

extern s32 func_8001E7E4(s32);

s32 func_8001D414(void) {
    if (func_8001E7E4(3) != 0) {
        return 2;
    }
    return func_8001E7E4(2) != 0;
}
