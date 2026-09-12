#include "common.h"

typedef struct S_8195EE48_0 {
    u8 pad_00[0x3C];
    s16 unk_3C;
    u8 pad_3E[0xA];
    s16 unk_48;
    u8 pad_4A[0x2];
    s16 unk_4C;
    u8 pad_4E[0x12];
    s16 unk_60;
    s16 unk_62;
} S_8195EE48_0;   /* arg0 in func_8195EE48 */

typedef struct S_8195EE48_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8195EE48_1;   /* arg1 in func_8195EE48 */



extern s32 rand();
extern void func_8002472C(void) __attribute__((noreturn));
extern u16 D_80027330[5];

/* Interpolates height with jitter until the phase ends, then advances position by velocity. */
void func_8195EE48(S_8195EE48_0 *state, S_8195EE48_1 *motion)
{
    s32 phase_or_height;
    s16 ticks_left;
    s16 next_ticks;
    u16 counter;

    counter = D_80027330[0];
    phase_or_height = state->unk_48;
    D_80027330[0] = counter + 1;
    if (phase_or_height == 0) {
        ticks_left = state->unk_4C;
        if (ticks_left > 0) {
            s32 phase_or_height;
            phase_or_height = state->unk_3C;
            state->unk_3C =
                (u16)state->unk_3C +
                ((state->unk_62 + state->unk_60 - phase_or_height) / ticks_left);
            motion->unk_08.at02.v =
                ((u16)state->unk_3C + (rand(phase_or_height, ticks_left) & 3)) - 2;
        }
        next_ticks = (u16)state->unk_4C - 1;
        state->unk_4C = next_ticks;
        if ((next_ticks << 16) <= 0) {
            state->unk_4C = 0x20;
            state->unk_48 = (u16)state->unk_48 + 1;
            func_8002472C();
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
