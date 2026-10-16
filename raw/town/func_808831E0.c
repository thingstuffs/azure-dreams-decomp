#include "common.h"
#include "m2c_compat.h"

s32 func_80700928(s32);                             /* extern */
M2C_UNK func_80700998(s32, M2C_UNK);                /* extern */
s32 func_80700A78();                                /* extern */
M2C_UNK func_80700BD8(u16);                         /* extern */
M2C_UNK func_80700C28(M2C_UNK);                     /* extern */
s32 func_80700C7C(u16);                             /* extern */

s32 func_807009E0(s32 arg0) {
    if ((func_80700C7C(*(u16 *)0x80700716) == 0) && (func_80700C7C(0x107U) != 0)) {
        if (func_80700928(arg0) != 0) {
            func_80700BD8(M2C_FIELD(((arg0 * 4) + 0x80700000), u16 *, 0x724));
            func_80700C28(0x107);
            return func_80700A78();
        }
        goto block_5;
    }
block_5:
    func_80700998(arg0, 0);
    return arg0;
}
