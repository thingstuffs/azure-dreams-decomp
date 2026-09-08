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

/* Advance active entry counters, drain ready flags, and apply the combined flags unless suppressed. */
void func_8005ACDC(void)
{
    s32 entry_index;
    s32 flags;

    flags = 0;
    if (D_80073828[0] == 0) {
        for (entry_index = 0; entry_index < D_80073734[0]; entry_index++) {
            if (D_80085458[entry_index].f1a != 0) {
                if (func_8005EB78(D_80073740[entry_index]) == 3) {
                    s32 dispatch_state;
                    u32 counter;

                    counter = D_80085458[entry_index].f1a;
                    if (counter >= 2) {
                        flags |= D_80073740[entry_index];
                        do {
                            func_8005E97C(0, D_80073740[entry_index]);
                            dispatch_state = func_8005EB78(D_80073740[entry_index]);
                        } while (dispatch_state != 2 && dispatch_state != 0);
                        D_80085458[entry_index].f1a = 0;
                    } else {
                        D_80085458[entry_index].f1a = counter + 1;
                    }
                }
            }
        }
    }

    if (flags != 0) {
        func_8005E97C(0, flags);
    }
}
