#include "common.h"
#include "m2c_compat.h"

M2C_UNK *func_80016E00();                        /* extern */
s32 func_800178A8();             /* extern */
M2C_UNK *func_80017960(); /* extern */
s32 func_8001868C();                         /* extern */
s32 func_80018868();                /* extern */
M2C_UNK func_800188E8();       /* extern */
extern M2C_UNK D_800189BC;
extern M2C_UNK D_80018B94;
extern M2C_UNK D_8001A04A;

M2C_UNK *func_806D4430(s32 arg0, s32 arg1, s32 arg2) {
    M2C_UNK *result;
    s32 temp_s0;

    result = func_80016E00(arg2);
    if (result != NULL) {
        return result;
    }
    result = func_80017960(&D_800189BC, &D_80018B94, arg0, arg2);
    temp_s0 = func_80018868(0x990, 2);
    if (func_8001868C(0x997) == 0) {
        temp_s0++;
        if (temp_s0 == 3) {
            temp_s0 = 0;
        }
        func_800188E8(0x990, temp_s0, 2);
    }
    if ((arg2 == 0xB) && (func_800178A8(&D_800189BC, arg0, 0xB) != 0)) {
        result = &D_8001A04A;
    }
    return result;
}

/* MECHANISM: Preserve the unused middle ABI argument so arg2 arrives in a2 and
   merge both result paths into s1 and mutate the cursor directly in s0.
   The cdk schedule fills the early branch slot and preserves the 0x28 frame. */
