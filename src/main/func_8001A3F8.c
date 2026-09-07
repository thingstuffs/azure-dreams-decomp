#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_804014E4();                            /* extern */
s32 func_80408664();                             /* extern */

s32 func_8001A3F8(s32 arg0) {
    func_804014E4();
    do {

    } while (func_80408664(arg0) == 0);
    *(s32 *)0x80409500 = 0;
    *(s32 *)0x804094E8 = 1;
    return 1;
}
