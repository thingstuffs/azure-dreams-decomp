#include "common.h"

extern s32 func_80019A44(s32);

/* Return 2 if check 3 succeeds, otherwise return the boolean result of check 2. */
s32 select_data_pointer_based_result(void) {
    if (func_80019A44(3) != 0) {
        return 2;
    }
    return func_80019A44(2) != 0;
}
