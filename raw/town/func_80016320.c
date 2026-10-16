#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8004B248(s32);                         /* extern */
M2C_UNK func_800B39E4(s32);                         /* extern */

void func_800B3A80(void *arg0) {
    if (arg0 != NULL) {
        func_8004B248(arg0 + 0xCC);
        func_800B39E4(M2C_FIELD((arg0 + 0x20), s32 *, 0xA8));
        M2C_FIELD(arg0, u16 *, 0x1E) = (u16) (M2C_FIELD(arg0, u16 *, 0x1E) | 0x8000);
        *(s32 *)0x800814A0 |= 0x8000;
    }
}
