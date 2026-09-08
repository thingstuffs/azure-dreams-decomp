#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_804013F8();                         /* extern */
M2C_UNK func_804014E4();                            /* extern */
M2C_UNK func_80408654();                     /* extern */

/* Run setup for both indices and apply the stored value. */
void func_80019908(void) {
    func_804014E4();
    func_80408654(0);
    func_80408654(1);
    func_804013F8(*(s32 *)0x804094EC);
}
