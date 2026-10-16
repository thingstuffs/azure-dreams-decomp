#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017480(s16, s16, s16, s16, s32);     /* extern */
s32 func_80017BEC(s16);                             /* extern */
M2C_UNK func_8001D4AC(void *, s16);                 /* extern */
M2C_UNK func_8001D5D8(void *, s16);                 /* extern */

void func_8001CE44(void *arg0, s16 arg1) {
    do {
        func_8001D5D8(arg0, arg1);
        func_8001D4AC(arg0, arg1);
    } while ((func_80017BEC(arg1) << 0x10) == 0);
    func_80017480(M2C_FIELD(arg0, s16 *, 0), M2C_FIELD(arg0, s16 *, 2), M2C_FIELD(arg0, s16 *, 4), M2C_FIELD(arg0, s16 *, 6), 0xF);
}
