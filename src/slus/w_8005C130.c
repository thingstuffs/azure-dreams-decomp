#include "common.h"

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

/* Dispatches to the first done or empty slot and returns the result, or -1 if none is available. */
s16 func_8005C130(s16 dispatch_arg0, s16 dispatch_arg1, s16 dispatch_arg2, s16 dispatch_arg3, s16 dispatch_arg4, s16 dispatch_arg5, s16 dispatch_arg6)
{
    s32 slot;

    D_80085F98[0] = 1;

    slot = 0;
    for (;;) {
        if (func_8005EB78(D_80073740[slot]) == 0) {
            goto checked_done_slots;
        }
        slot++;
        if (slot > D_80073734[0] - 1) {
            slot = -1;
            break;
        }
    }
checked_done_slots:

    if (slot == -1) {
        slot = 0;
        for (;;) {
            if (D_80085458[slot].f1a == 0) {
                goto checked_empty_slots;
            }
            slot++;
            if (slot > D_80073734[0] - 1) {
                slot = -1;
                break;
            }
        }
    checked_empty_slots:
        ;
    }

    if (slot != -1) {
        slot = func_8005BBFC((s16) slot, dispatch_arg0, dispatch_arg1, dispatch_arg2, dispatch_arg3, dispatch_arg4, dispatch_arg5, dispatch_arg6);
    }

    D_80085F98[0] = 0;
    return slot;
}
