#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003832C();                         /* extern */
s32 func_80053EF0();                         /* extern */

/* Call the handler when check 4 returns zero. */
void func_800382F0(s32 handler_arg) {
    if (func_80053EF0(4) == 0) {
        func_8003832C(handler_arg);
    }
}
