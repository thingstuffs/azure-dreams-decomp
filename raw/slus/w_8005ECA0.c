#include "common.h"

/* S_80079970: shift-input value holder; only element 0 (a u16 view) is
 * touched here. Declared as an incomplete-size s32 array (matches sibling
 * D_80079980's array-of-3 convention) so its total size exceeds 8 bytes and
 * codegen uses %hi/%lo (not $gp-relative) addressing. */
extern s32 D_80079970[4];

/* S_80079980: shift-amount table shared with func_8005D598/func_8005D63C/
 * func_8005D550/func_8005D1D0/etc; only index 0 is read here. */
extern s32 D_80079980[3];

extern s32 func_8005D598(s32 a0, s32 a1);

/* func_8005ECA0: Validates that a0 lies within a fixed address/id window
 * [0x1010, 0x1010+0x7EFE8]; if it does, asks func_8005D598 for a value
 * (mode -1) using a0 as the second argument, latches the low 16 bits of that
 * value into D_80079970, and returns that 16-bit value left-shifted by the
 * global shift amount D_80079980[0]. Returns 0 if a0 is out of range. */
s32 func_8005ECA0(s32 a0)
{
    u16 v;

    if ((u32)(a0 - 0x1010) > 0x7EFE8) {
        return 0;
    }

    v = (u16)func_8005D598(-1, a0);
    *(u16 *)D_80079970 = v;
    return (s32)v << D_80079980[0];
}
