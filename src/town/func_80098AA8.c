#include "common.h"
#include "m2c_compat.h"

s32 func_80096368(s32 *);                           /* extern */
s32 func_80096440();                           /* extern */
M2C_UNK func_800966C8();                  /* extern */
M2C_UNK func_800966F8();                  /* extern */
extern s32 D_800FE5CC;

/* Applies fixed-point boundary corrections according to D_800FE5CC. */
void func_80096208(s32 *value) {
    s32 upper_bound;
    s32 neutral_upper_bound;
    s32 lower_bound;

    if (D_800FE5CC > 0) {
        upper_bound = func_80096368(value) << 0x10;
        if (*value >= upper_bound) {
            func_800966C8(value, upper_bound);
            return;
        }
    } else {
        if (D_800FE5CC >= 0) {
            neutral_upper_bound = func_80096368(value) << 0x10;
            if (*value >= neutral_upper_bound) {
                func_800966C8(value, neutral_upper_bound);
            }
        }
        lower_bound = (func_80096440(value) << 0x10) - 1;
        if (lower_bound >= *value) {
            func_800966F8(value, lower_bound);
        }
    }
}
