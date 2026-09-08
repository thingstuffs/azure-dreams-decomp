#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001E578();                     /* extern */
s32 func_8001E670();                         /* extern */

/* Invoke func_8001E578 for 0x406 and 0x401 when the 0x406 check returns zero. */
void func_8001BA8C(void) {
    if (func_8001E670(0x406) == 0) {
        func_8001E578(0x406);
        func_8001E578(0x401);
    }
}
