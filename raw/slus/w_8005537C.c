#include "common.h"

/* Applies an optional octave-down shift (-0x18) to a note value based on flag bit 0x20 in D_800847D0[0], clamps it via func_80055750, and stores the result into both S_800848F8.unk08 and .unk0A. */
typedef struct S_800848F8 {
    u8 pad00[8];
    s16 unk08;
    s16 unk0A;
} S_800848F8;

extern s32 D_800847D0[3];
extern S_800848F8 D_800848F8;
extern s32 func_80055750(s16 arg0);

void func_8005537C(s32 arg0) {
    s32 v;

    D_800848F8.unk0A = (s16) arg0;
    if (D_800847D0[0] & 0x20) {
        D_800848F8.unk0A = (s16) (arg0 - 0x18);
    }
    v = func_80055750(D_800848F8.unk0A);
    D_800848F8.unk0A = (s16) v;
    D_800848F8.unk08 = (s16) v;
}
