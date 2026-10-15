#ifndef SLUS_GP_SPLIT_STORAGE_H
#define SLUS_GP_SPLIT_STORAGE_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/game_work.h"

/* S_80083164: state/generation counter global; only offset 0 (u16) is
 * ever read across the sibling family (func_80047338/func_80047468/
 * func_8003E758). Declared >8 bytes (padded out to the next known
 * symbol D_80083170) to force %hi/%lo addressing instead of $gp-rel. */
struct S_80083164 {
    u16 field_0;
    u8 pad2[0xA];
};



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

extern u16 D_80080B10;
extern u16 D_80080B12;
extern u16 D_80080B14;
void func_80048660(struct S_80048660 *state);

#endif
