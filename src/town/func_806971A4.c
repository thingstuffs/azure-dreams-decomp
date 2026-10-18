#include "common.h"
#include "m2c_compat.h"

s32 func_800179A0(void);
s32 func_80017B24();         /* extern */
s32 * func_80017BDC(void *, void *, s32, s32);
s32 func_80018820();                                /* extern */
extern M2C_UNK D_8001895C;
extern s32 D_80018AD0;
extern M2C_UNK D_80019B97;

/* Retrieves a result and substitutes the fallback when the follow-up check succeeds. */
s32 *func_806971A4(s32 key, s32 unused, s32 context) {
    s32 *result;

    if (func_80018820() >= 0xA) {
        func_800179A0();
    }
    result = func_80017BDC(&D_8001895C, &D_80018AD0, key, context);
    if (func_80017B24(&D_8001895C, key, context) != 0) {
        result = &D_80019B97;
    }
    return result;
}
