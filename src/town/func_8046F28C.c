#include "common.h"
#include "m2c_compat.h"

s32 func_80016164(s32 first_value, s32 second_value);                                /* extern */
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

M2C_UNK *func_8001628C(s32 first_value, s32 second_value) {
    M2C_UNK *result;
    s32 value;

    if (func_80016164(first_value, second_value) != 0) {
        result = &D_8001EC04;
    } else {
        value = func_8001A7F8();
        if ((func_8001A510(0x79A) == 0) && ((value < 5) || (func_80016224(0x47E, 0x79A) != 0))) {
            result = &D_8001E2F8;
            func_8001A418(0x47E);
        } else if ((func_8001A510(0x79B) == 0) && ((value < 0xA) || (func_80016224(0x47E, 0x79B) != 0))) {
            result = &D_8001E634;
            func_8001A418(0x47E);
        } else if ((func_8001A510(0x79C) == 0) && ((value < 0xF) || (func_80016224(0x47E, 0x79C) != 0))) {
            result = &D_8001E79C;
            func_8001A418(0x47E);
        } else if ((func_8001A510(0x79D) == 0) && (((value < 0x19) && (func_800161C8() != 0))
            || (func_80016224(0x47E, 0x79D) != 0))) {
            result = &D_8001E9C0;
            func_8001A418(0x47E);
        } else {
            result = &D_8001EB10;
        }
        func_8001A418(0x7A3);
    }
    return result;
}
/* MECHANISM: The true-space CFG turns apparent func_80016398/B0/B8 calls into local joins.
   One s0 result pointer reproduces the 0x18 frame and tail layout.
   Omitting func_800161C8's explicit arg reuses the branch-delay a0 setup and closes word 58. */
