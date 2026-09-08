#include "common.h"

extern s32 func_800198D0(s32);
extern s32 D_8001638C;
extern s32 D_80017598;

/* Select alternate output data when condition 0x3F5 is clear and condition 0x14 is set. */
s32 *func_8001753C(s32 **out_data) {
    if (func_800198D0(0x3F5) == 0) {
        if (func_800198D0(0x14) != 0) {
            *out_data = &D_80017598;
            return 0;
        }
    }
    return &D_8001638C;
}
