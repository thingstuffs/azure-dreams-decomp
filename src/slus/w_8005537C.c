#include "common.h"

typedef struct S_800848F8 {
    u8 pad00[8];
    s16 unk08;
    s16 unk0A;
} S_800848F8;

extern s32 D_800847D0[3];
extern S_800848F8 D_800848F8;
extern s32 func_80055750(s16 arg0);

/* Optionally lowers the note by 0x18, clamps it, and stores it in both note fields. */
void func_8005537C(s32 note) {
    s32 clamped_note;

    D_800848F8.unk0A = (s16) note;
    if (D_800847D0[0] & 0x20) {
        D_800848F8.unk0A = (s16) (note - 0x18);
    }
    clamped_note = func_80055750(D_800848F8.unk0A);
    D_800848F8.unk0A = (s16) clamped_note;
    D_800848F8.unk08 = (s16) clamped_note;
}
