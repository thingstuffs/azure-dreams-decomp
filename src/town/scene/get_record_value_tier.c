#include "common.h"

s32 func_8001A7B0(s32);

/* Return 2 if check 3 succeeds, otherwise return whether check 2 succeeds. */
s32 get_record_value_tier(void) {
    if (func_8001A7B0(3) != 0) {
        return 2;
    }
    return func_8001A7B0(2) != 0;
}
