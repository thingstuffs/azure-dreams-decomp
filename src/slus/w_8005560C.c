#include "common.h"

/* S_80084808: single s16 field at offset 0; matches the existing globals.h
   decl `extern short D_80084808[8];` (only element 0 is touched here). */
typedef struct S_80084808 {
    s16 unk00;
} S_80084808;

extern void func_8005BAB0(void);
extern s32 func_80055750(s16 arg0);
extern s32 func_8003E14C(void);
extern s32 func_8005B4D0(s32 a0, void *a1, u16 a2, u16 a3, s32 a4);

extern u16 D_800847EE[8];   /* size>8 forces %hi/%lo addressing */
extern s16 D_80084808[8];

/* summary: Splits a "gauge" value (D_80084808[0], scaled against D_800847EE[0]
   and, doubled, against func_8003E14C()'s secondary max) into fractions of
   32767, clamps the primary fraction via func_80055750, and issues one
   func_8005B4D0 draw/update call for it, or two calls (primary remainder +
   overflow segment) if the doubled fraction is nonzero. */
void func_8005560C(s32 a0, void *a1)
{
    s32 v0;
    s32 s2;
    s32 s0;

    func_8005BAB0();

    v0 = D_800847EE[0] * D_80084808[0];
    s2 = func_80055750((s16)(v0 / 32767));

    v0 = func_8003E14C();
    s0 = (v0 * (D_80084808[0] + D_80084808[0])) / 32767;

    if (s0 == 0) {
        func_8005B4D0(a0, a1, s2, s2, 0);
    } else {
        s2 -= s0;
        func_8005B4D0(a0, a1, s2, s2, 0);
        func_8005B4D0(a0, a1, s0, s0, 1);
    }
}
