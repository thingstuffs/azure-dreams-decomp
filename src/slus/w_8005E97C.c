#include "common.h"

typedef struct {
    u8  pad[0x188];
    volatile u16 keyon_lo;   /* 0x188 */
    volatile u16 keyon_hi;   /* 0x18A */
    u16 keyoff_lo;  /* 0x18C */
    u16 keyoff_hi;  /* 0x18E */
} SpuRegs;

extern SpuRegs *D_80079958;
extern volatile s32 D_800794F0;
extern volatile s32 D_80079518;
extern volatile s32 D_8007951C;
extern s32 D_80079950;
extern volatile u16 D_80086D58[2];
extern volatile u16 D_80086D5C;
extern volatile u16 D_80086D5E;

/* PsyQ 4.0 LIBSPU: SpuSetKey */
void func_8005E97C(s32 onOff, u32 voices)
{
    u16 lo;
    u16 hi;

    voices &= 0xFFFFFF;
    lo = voices;
    hi = voices >> 16;

    switch (onOff) {
    case 1:
        if (D_80079950 & 1) {
            D_80086D58[0] = lo;
            D_80086D58[1] = hi;
            D_8007951C |= 1;
            D_80079518 |= voices;
            if (D_80086D5C & voices) {
                D_80086D5C &= ~voices;
            }
            if (D_80086D5E & hi) {
                D_80086D5E &= ~hi;
            }
        } else {
            s32 t = D_800794F0;
            D_80079958->keyon_lo = lo;
            D_80079958->keyon_hi = hi;
            D_800794F0 = t | voices;
        }
        break;

    case 0:
        if (D_80079950 & 1) {
            D_80086D5C = lo;
            D_80086D5E = hi;
            D_8007951C |= 1;
            D_80079518 &= ~voices;
            if (D_80086D58[0] & voices) {
                D_80086D58[0] &= ~voices;
            }
            if (D_80086D58[1] & hi) {
                D_80086D58[1] &= ~hi;
            }
        } else {
            D_80079958->keyoff_lo = lo;
            D_80079958->keyoff_hi = hi;
            D_800794F0 &= ~voices;
        }
        break;
    }
}
