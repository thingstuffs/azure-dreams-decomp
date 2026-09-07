#include "common.h"
#include "m2c_compat.h"

s32 func_80016164();                                /* extern */
s32 func_800161C8();                         /* extern */
s32 func_80016224();                /* extern */
M2C_UNK func_8001A418();                     /* extern */
s32 func_8001A510();                         /* extern */
s32 func_8001A7F8();                                /* extern */
extern M2C_UNK D_8001E2F8;
extern M2C_UNK D_8001E634;
extern M2C_UNK D_8001E79C;
extern M2C_UNK D_8001E9C0;
extern M2C_UNK D_8001EB10;
extern M2C_UNK D_8001EC04;

M2C_UNK *func_8001628C(void) {
    M2C_UNK *var_s0;
    s32 temp_s0;

    if (func_80016164() != 0) {
        var_s0 = &D_8001EC04;
        goto done;
    }
    temp_s0 = func_8001A7F8();
    if ((func_8001A510(0x79A) == 0) && ((temp_s0 < 5) || (func_80016224(0x47E, 0x79A) != 0))) {
        var_s0 = &D_8001E2F8;
        goto selected;
    }
    if ((func_8001A510(0x79B) == 0) && ((temp_s0 < 0xA) || (func_80016224(0x47E, 0x79B) != 0))) {
        var_s0 = &D_8001E634;
        goto selected;
    }
    if ((func_8001A510(0x79C) == 0) && ((temp_s0 < 0xF) || (func_80016224(0x47E, 0x79C) != 0))) {
        var_s0 = &D_8001E79C;
        goto selected;
    }
    if (func_8001A510(0x79D) != 0) {
        goto use_default;
    }
    if ((temp_s0 < 0x19) && (func_800161C8() != 0)) {
        goto select_last;
    }
    if (func_80016224(0x47E, 0x79D) != 0) {
        goto select_last;
    }
    goto use_default;
select_last:
    var_s0 = &D_8001E9C0;
selected:
    func_8001A418(0x47E);
    goto finalize;
use_default:
    var_s0 = &D_8001EB10;
finalize:
    func_8001A418(0x7A3);
done:
    return var_s0;
}
/* MECHANISM: The true-space CFG turns apparent func_80016398/B0/B8 calls into local joins.
   One s0 result pointer and shared selection labels reproduce the 0x18 frame and tail layout.
   Omitting func_800161C8's explicit arg reuses the branch-delay a0 setup and closes word 58. */
