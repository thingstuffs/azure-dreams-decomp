#include "common.h"

extern s32 D_8001673C[];
extern s32 D_80016754[];
extern s32 D_800170CC[];
extern s32 D_80019BB4[3];

extern s32 func_80018FC8(s32 *, s32 *, s32, s32);

/* Returns the selected table value for mode 1, or delegates the lookup for other modes. */
s32 func_80017CC0(s32 lookupInput, s32 unused, s32 mode) {
    s32 result;

    if (mode != 1) {
        result = func_80018FC8(D_8001673C, D_800170CC, lookupInput, mode);
    } else {
        result = D_80016754[D_80019BB4[0]];
    }
    return result;
}
