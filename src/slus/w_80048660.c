#include "common.h"

/* Per-frame scroll/animation stepper: resets the accumulator triple
 * (D_80080B10/12/14) whenever the session generation counter
 * D_80083164 changes from the last-seen value D_80081530, then
 * accumulates arg0's row/col deltas into the shared position/carry
 * state and writes back the current position into arg0->field_8/9. */
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

void func_80048660(struct S_80048660 *arg0)
{
    s32 temp_a1;
    s32 temp_a2;

    if (D_80083164.field_0 != D_80081530) {
        D_80080B14 = 0;
        D_80080B12 = 0;
        D_80080B10 = 0;
        D_80081530 = D_80083164.field_0;
    }

    temp_a1 = (s32)(arg0->field_A + 1) >> 1;
    temp_a2 = arg0->field_B + 1;

    if ((s32)(D_80080B12 + temp_a2) >= 0x100) {
        D_80080B10 = D_80080B10 + D_80080B14;
        D_80080B12 = 0;
    }

    if ((s32)(D_80080B10 + temp_a1) >= 0x20) {
        D_80080B10 = 0;
        D_80080B12 = 0;
        D_80080B14 = 0;
    }

    arg0->field_8 = (s8)(D_80080B10 << 1);
    arg0->field_9 = (u8)D_80080B12;

    if ((s32)D_80080B14 < temp_a1) {
        D_80080B14 = (u16)temp_a1;
    }

    D_80080B12 = D_80080B12 + temp_a2;
}
