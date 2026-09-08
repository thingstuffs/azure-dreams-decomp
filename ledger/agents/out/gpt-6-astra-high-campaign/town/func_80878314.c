#include "common.h"

s32 func_80702714();                             /* extern */

/* Return 2 when the selected flag is set and flag 0x1F9 is clear. */
s32 func_80702314(void) {
    s32 result;

    result = 0;
    if (func_80702714(*(u16 *)0x80701DCE) != 0) {
        result = (func_80702714(0x1F9U) == 0) * 2;
    }
    return result;
}
