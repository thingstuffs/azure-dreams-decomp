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

/* Latch and shift the value for an in-range address, or return zero. */
s32 func_8005ECA0(s32 address)
{
    u16 shift_input;

    if ((u32)(address - 0x1010) > 0x7EFE8) {
        return 0;
    }

    shift_input = (u16)func_8005D598(-1, address);
    *(u16 *)D_80079970 = shift_input;
    return (s32)shift_input << D_80079980[0];
}
