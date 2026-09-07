#include "common.h"

/* Finds a free slot: first scans D_80073740[0..D_80073734[0]-1] via
 * func_8005EB78 for an entry that reports "done" (0); if none is free,
 * falls back to scanning D_80085458 for a slot whose f1a field is 0. If a
 * free slot is found (by either scan), dispatches it via func_8005BBFC with
 * the found index and the 6 remaining (s16) parameters, and returns its
 * (s16) result; otherwise returns -1. */
/* D_80073734: s32 count array (established elsewhere; index 0 = active-entry count). */
extern s32 D_80073734[4];

/* D_80073740: s32 flag-value array, one entry per D_80085458 slot. */
extern s32 D_80073740[64];

/* S_80085458: D_80085458 element, stride 0x78 (120) bytes; only field f1a
 * (u16, offset 0x1A) is touched by this function. */
typedef struct S_80085458 {
    /* 0x00 */ u8 pad00[0x1A];
    /* 0x1A */ u16 f1a;
    /* 0x1C */ u8 pad1c[0x78 - 0x1C];
} S_80085458;

extern S_80085458 D_80085458[64];

/* D_80085F98: mode/busy flag, set while this function runs. */
extern s32 D_80085F98[4];

extern s32 func_8005EB78(s32 a0);
extern s16 func_8005BBFC(s16 idx, s16 a0, s16 a1, s16 a2, s16 a3, s16 a4, s16 a5, s16 a6);

s16 func_8005C130(s16 a0, s16 a1, s16 a2, s16 a3, s16 a4, s16 a5, s16 a6)
{
    s32 i;

    D_80085F98[0] = 1;

    i = 0;
    for (;;) {
        if (func_8005EB78(D_80073740[i]) == 0) {
            goto found1;
        }
        i++;
        if (i > D_80073734[0] - 1) {
            i = -1;
            break;
        }
    }
found1:

    if (i == -1) {
        i = 0;
        for (;;) {
            if (D_80085458[i].f1a == 0) {
                goto found2;
            }
            i++;
            if (i > D_80073734[0] - 1) {
                i = -1;
                break;
            }
        }
    found2:
        ;
    }

    if (i != -1) {
        i = func_8005BBFC((s16) i, a0, a1, a2, a3, a4, a5, a6);
    }

    D_80085F98[0] = 0;
    return i;
}
