#include "common.h"

s32 func_80702714();                             /* extern */

s32 func_80702314(void) {
    s32 var_v0;

    var_v0 = 0;
    if (func_80702714(*(u16 *)0x80701DCE) != 0) {
        var_v0 = (func_80702714(0x1F9U) == 0) * 2;
    }
    return var_v0;
}
