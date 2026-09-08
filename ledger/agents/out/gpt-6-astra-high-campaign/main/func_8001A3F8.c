#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_804014E4();                            /* extern */
s32 func_80408664();                             /* extern */

/* Wait for the selected poll to succeed, then clear the pending flag and set the ready flag. */
s32 func_8001A3F8(s32 poll_id) {
    func_804014E4();
    do {

    } while (func_80408664(poll_id) == 0);
    *(s32 *)0x80409500 = 0;
    *(s32 *)0x804094E8 = 1;
    return 1;
}
