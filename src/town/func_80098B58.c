#include "common.h"
#include "m2c_compat.h"

s32 func_80096518(s32 *);                           /* extern */
s32 func_800965F0();                           /* extern */
void townSetGlobal800CFCEDInitializeCallCallee800954DC();                  /* extern */
void townSetGlobal800CFCECInitializeCallCallee800954DC();                  /* extern */
extern s32 D_800FE5D0;

/* Applies fixed-point boundary corrections according to D_800FE5D0. */
void func_800962B8(s32 *value) {
    s32 upper_bound;
    s32 neutral_upper_bound;
    s32 lower_bound;

    if (D_800FE5D0 > 0) {
        upper_bound = func_80096518(value) << 0x10;
        if (value[1] >= upper_bound) {
            townSetGlobal800CFCEDInitializeCallCallee800954DC(value, upper_bound);
            return;
        }
    } else {
        if (D_800FE5D0 >= 0) {
            neutral_upper_bound = func_80096518(value) << 0x10;
            if (value[1] >= neutral_upper_bound) {
                townSetGlobal800CFCEDInitializeCallCallee800954DC(value, neutral_upper_bound);
            }
        }
        lower_bound = (func_800965F0(value) << 0x10) - 1;
        if (lower_bound >= value[1]) {
            townSetGlobal800CFCECInitializeCallCallee800954DC(value, lower_bound);
        }
    }
}
