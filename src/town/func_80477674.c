#include "common.h"

extern s32 func_80019A44(s32);

/* Return 2 if check 3 succeeds, otherwise return the boolean result of check 2. */
s32 func_80018674(void) {
    if (func_80019A44(3) != 0) {
        return 2;
    }
    return func_80019A44(2) != 0;
}
