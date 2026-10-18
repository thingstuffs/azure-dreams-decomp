#include "common.h"
#include "m2c_compat.h"

s32 func_800179A0(void);
s32 func_80017B24();         /* extern */
s32 * func_80017BDC(void *, void *, s32, s32);
s32 func_80018820();                                /* extern */
extern M2C_UNK D_80018964;
extern s32 D_80018AD0;
extern M2C_UNK D_80019BD1;

/* Look up an entry and return the fallback when its check succeeds. */
s32 *func_8069725C(s32 entry_id, s32 unused, s32 context) {
    s32 *entry;

    if (func_80018820() >= 0x14) {
        func_800179A0();
    }
    entry = func_80017BDC(&D_80018964, &D_80018AD0, entry_id, context);
    if (func_80017B24(&D_80018964, entry_id, context) != 0) {
        entry = &D_80019BD1;
    }
    return entry;
}
