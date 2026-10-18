#include "common.h"

extern s32 func_80019A44(s32);

/* Return 2 if check 3 succeeds; otherwise return whether check 2 succeeds. */
s32 select_data_pointer_based_result(void) {
    if (func_80019A44(3) != 0) {
        return 2;
    }
    return func_80019A44(2) != 0;
}
