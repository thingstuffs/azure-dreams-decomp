#include "common.h"

s32 rand();                                /* extern */

s32 func_80024EA4(void) {
    s32 var_v0;

    var_v0 = rand() & 1;
    if (var_v0 == 0) {
        var_v0 = -1;
    }
    return var_v0;
}
