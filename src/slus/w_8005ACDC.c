#include "common.h"

/* D_80073828: short flag array (established in code.c: index 0 set by func_8005ACD0). */
extern short D_80073828[5];

/* D_80073734: s32 count array (established elsewhere; index 0 = active-entry count). */
extern s32 D_80073734[4];

/* D_80073740: s32 flag-value array, one entry per D_80085458 slot. */
extern s32 D_80073740[];

/* S_8005ACDC_85458: D_80085458 element, stride 0x78; only field f1a (u16, offset
 * 0x1A) is touched by this function. */
typedef struct S_8005ACDC_85458 {
    /* 0x00 */ u8 pad00[0x1A];
    /* 0x1A */ u16 f1a;
    /* 0x1C */ u8 pad1c[0x78 - 0x1C];
} S_8005ACDC_85458;

extern S_8005ACDC_85458 D_80085458[64];

extern s32 func_8005EB78(s32 a0);
extern void func_8005E97C(s32 a0, s32 a1);

/* Per-frame "damage-over-time flag" processor: for each of the first
 * D_80073734[0] entries with an active f1a counter, checks func_8005EB78's
 * dispatch state; on state 3 either bumps the counter (states 0-1) or, once
 * the counter has saturated at >=2, OR-accumulates its D_80073740 flag value
 * and drains it via func_8005E97C until func_8005EB78 reports done (0) or
 * cancelled (2), then clears the counter. Finally re-broadcasts the
 * accumulated flags once via func_8005E97C, unless D_80073828[0] is set
 * (global suppression) or there are no active entries. */
void func_8005ACDC(void)
{
    s32 i;
    s32 flags;

    flags = 0;
    if (D_80073828[0] == 0) {
        for (i = 0; i < D_80073734[0]; i++) {
            if (D_80085458[i].f1a != 0) {
                if (func_8005EB78(D_80073740[i]) == 3) {
                    s32 v0;
                    u32 v1;

                    v1 = D_80085458[i].f1a;
                    if (v1 >= 2) {
                        flags |= D_80073740[i];
                        do {
                            func_8005E97C(0, D_80073740[i]);
                            v0 = func_8005EB78(D_80073740[i]);
                        } while (v0 != 2 && v0 != 0);
                        D_80085458[i].f1a = 0;
                    } else {
                        D_80085458[i].f1a = v1 + 1;
                    }
                }
            }
        }
    }

    if (flags != 0) {
        func_8005E97C(0, flags);
    }
}
