#include "modules/dungeon_ovl_197e800.h"
#include "common.h"

   /* arg0 in func_80024648 */

   /* arg1 in func_80024648 */


extern s32 rand();

/* Interpolates height with jitter until the phase ends, then advances position by velocity. */
void func_80024648(S_8195EE48_0 *state, S_8195EE48_1 *motion)
{
    s32 phase_or_height;
    s16 ticks_left;
    s16 next_ticks;
    u16 counter;

    counter = (*(u16 *)&D_80027330);
    phase_or_height = state->unk_48;
    (*(u16 *)&D_80027330) = counter + 1;
    if (phase_or_height == 0) {
        ticks_left = state->unk_4C;
        if (ticks_left > 0) {
            s32 phase_or_height;
            phase_or_height = state->unk_3C;
            state->unk_3C =
                (u16)state->unk_3C +
                ((state->unk_62 + state->unk_60 - phase_or_height) / ticks_left);
            motion->unk_08.at02.v =
                ((u16)state->unk_3C + (rand() & 3)) - 2;
        }
        next_ticks = (u16)state->unk_4C - 1;
        state->unk_4C = next_ticks;
        if ((next_ticks << 16) <= 0) {
            state->unk_4C = 0x20;
            state->unk_48 = (u16)state->unk_48 + 1;
            return;
        }
    } else {
        motion->unk_00 += motion->unk_0C;
        motion->unk_04 += motion->unk_10;
        motion->unk_08.at00.v += motion->unk_14;
    }
}

/* MECHANISM: An s32-held 0x48 condition produces retail's signed load and exact s0/s1/ra frame.
   Reading the counter first preserves retail emission order; a guarded $v1 runtime-value pin
   fixes the final counter/base coloring while the natural CFG retains both delay-slot stores. */
