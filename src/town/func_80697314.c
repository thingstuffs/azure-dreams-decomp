#include "common.h"
#include "shared/town_lookup_data.h"
#include "m2c_compat.h"

s32 func_800179A0(void);
s32 func_80017B24();         /* extern */
s32 * func_80017BDC(void *, void *, s32, s32);
s32 func_80018820();                                /* extern */
extern s32 D_80018AD0;
extern M2C_UNK D_80019C79;

/* Resolve a selection and return the fallback entry when its check succeeds. */
s32 *func_80697314(s32 selection_id, s32 unused, s32 context) {
    s32 *result;

    if (func_80018820() >= 0x1E) {
        func_800179A0();
    }
    result = func_80017BDC(&D_8001896C, &D_80018AD0, selection_id, context);
    if (func_80017B24(&D_8001896C, selection_id, context) != 0) {
        result = &D_80019C79;
    }
    return result;
}
