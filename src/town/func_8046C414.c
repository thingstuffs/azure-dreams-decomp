#include "common.h"

extern s32 func_8001E7E4(s32);

/* Return 2 when check 3 passes, otherwise return whether check 2 passes. */
s32 func_8001D414(void) {
    if (func_8001E7E4(3) != 0) {
        return 2;
    }
    return func_8001E7E4(2) != 0;
}
