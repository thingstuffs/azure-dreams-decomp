#include "common.h"
#include "m2c_compat.h"

s32 func_80017978();                    /* extern */
s32 func_80018604();                                /* extern */

/* Returns whether func_80017978 succeeds when func_80018604 is at least 10. */
s32 func_8067F2C0(s32 value, M2C_UNK data) {
    s32 succeeded;

    succeeded = 0;
    if (func_80018604() >= 0xA) {
        succeeded = func_80017978(value, data) != 0;
    }
    return succeeded;
}
