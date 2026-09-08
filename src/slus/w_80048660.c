#include "common.h"

/* S_80083164: state/generation counter global; only offset 0 (u16) is
 * ever read across the sibling family (func_80047338/func_80047468/
 * func_8003E758). Declared >8 bytes (padded out to the next known
 * symbol D_80083170) to force %hi/%lo addressing instead of $gp-rel. */
struct S_80083164 {
    u16 field_0;
    u8 pad2[0xA];
};

extern struct S_80083164 D_80083164;

extern u16 D_80081530;
extern u16 D_80080B10;
extern u16 D_80080B12;
extern u16 D_80080B14;

/* S_80048660: per-caller animation/scroll state passed by reference.
 * field_8/field_9 are outputs (written each call); field_A/field_B are
 * inputs (read-only counters used to derive step sizes). */
struct S_80048660 {
    char pad0[8];
    s8 field_8;
    u8 field_9;
    u8 field_A;
    u8 field_B;
};

/* Advances shared scroll coordinates, resetting them when the session generation changes. */
void func_80048660(struct S_80048660 *state)
{
    s32 row_step;
    s32 col_step;

    if (D_80083164.field_0 != D_80081530) {
        D_80080B14 = 0;
        D_80080B12 = 0;
        D_80080B10 = 0;
        D_80081530 = D_80083164.field_0;
    }

    row_step = (s32)(state->field_A + 1) >> 1;
    col_step = state->field_B + 1;

    if ((s32)(D_80080B12 + col_step) >= 0x100) {
        D_80080B10 = D_80080B10 + D_80080B14;
        D_80080B12 = 0;
    }

    if ((s32)(D_80080B10 + row_step) >= 0x20) {
        D_80080B10 = 0;
        D_80080B12 = 0;
        D_80080B14 = 0;
    }

    state->field_8 = (s8)(D_80080B10 << 1);
    state->field_9 = (u8)D_80080B12;

    if ((s32)D_80080B14 < row_step) {
        D_80080B14 = (u16)row_step;
    }

    D_80080B12 = D_80080B12 + col_step;
}
