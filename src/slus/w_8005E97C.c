#include "slus/sound_key_buffer.h"

/* Turns selected SPU voices on or off, queuing register writes when enabled. */
void func_8005E97C(s32 key_on, u32 voices)
{
    u16 voices_lo;
    u16 voices_hi;

    voices &= 0xFFFFFF;
    voices_lo = voices;
    voices_hi = voices >> 16;

    switch (key_on) {
    case 1:
        if (D_80079950 & 1) {
            D_80086D58[0] = voices_lo;
            D_80086D58[1] = voices_hi;
            D_8007951C |= 1;
            D_80079518 |= voices;
            if (D_80086D5C & voices) {
                D_80086D5C &= ~voices;
            }
            if (D_80086D5E & voices_hi) {
                D_80086D5E &= ~voices_hi;
            }
        } else {
            s32 active_voices = D_800794F0;
            ((SpuKeyRegs *)D_80079958)->keyon_lo = voices_lo;
            ((SpuKeyRegs *)D_80079958)->keyon_hi = voices_hi;
            D_800794F0 = active_voices | voices;
        }
        break;

    case 0:
        if (D_80079950 & 1) {
            D_80086D5C = voices_lo;
            D_80086D5E = voices_hi;
            D_8007951C |= 1;
            D_80079518 &= ~voices;
            if (D_80086D58[0] & voices) {
                D_80086D58[0] &= ~voices;
            }
            if (D_80086D58[1] & voices_hi) {
                D_80086D58[1] &= ~voices_hi;
            }
        } else {
            ((SpuKeyRegs *)D_80079958)->keyoff_lo = voices_lo;
            ((SpuKeyRegs *)D_80079958)->keyoff_hi = voices_hi;
            D_800794F0 &= ~voices;
        }
        break;
    }
}
