#include "common.h"

typedef struct S_800799BC {
    u32 field0;
    s32 field4;
} S_800799BC;

extern s32 D_80079980[3];
extern s32 D_800799B4[3];
extern s32 D_800799B8[3];
extern S_800799BC *D_800799BC[3];

/* Initializes and publishes the record-list head for a positive count, returning the count or zero. */
s32 func_8005D838(s32 count, S_800799BC *record) {
    register s32 result ASM_REG("v0") = count;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (result <= 0) {
        result = 0;
    } else {
        s32 shift = D_80079980[0];
        record->field0 = 0x40001010;
        D_800799BC[0] = record;
        D_800799B8[0] = 0;
        D_800799B4[0] = result;
        record->field4 = (0x10000 << shift) - 0x1010;
    }
    return result;
}
