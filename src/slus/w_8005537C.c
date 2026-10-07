#include "shared/sound_state.h"
#include "common.h"


extern s32 func_80055750(s16 clamp_input);

/* Optionally lowers the note by 0x18, clamps it, and stores it in both note fields. */
void func_8005537C(s32 note) {
    s32 clamped_note;

    D_800848F8.unk_0A = (s16) note;
    if (((s32)D_800847D0.flags00) & 0x20) {
        D_800848F8.unk_0A = (s16) (note - 0x18);
    }
    clamped_note = func_80055750(D_800848F8.unk_0A);
    D_800848F8.unk_0A = (s16) clamped_note;
    D_800848F8.unk_08 = (s16) clamped_note;
}
