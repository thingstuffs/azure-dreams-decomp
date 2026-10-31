/* Effect motion with a decaying delta and a timed color fade. */
#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800D6804_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800D6804_0;   /* state in advance_decaying_effect_state */

typedef struct S_800D6804_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    union { s16 s; u16 u; } unk_32;   /* accessed as both */
    s16 unk_34;
} S_800D6804_1;   /* arg0 in advance_decaying_effect_state */


/* Adds the current velocity to the position and reduces the velocity to three quarters. */
static __inline__ void decay_step(S_800D6804_0 *s)
{
    s->unk_08 += s->unk_14;
    s->unk_14 = s->unk_14 * 3 / 4;
}

/* Advance the state with a decaying delta and fade the effect color until its timer expires. */
void advance_decaying_effect_state(void *effect_arg, void *state_data)
{
    S_800D6804_1 *effect = effect_arg;
    s16 frames_left;

    decay_step((S_800D6804_0 *)state_data);

    effect->unk_04.at00.v =
        (effect->unk_00 * effect->unk_32.s) /
        effect->unk_34;
    effect->unk_04.at01.v =
        (effect->unk_01 * effect->unk_32.s) /
        effect->unk_34;
    effect->unk_04.at02.v =
        (effect->unk_02 * effect->unk_32.s) /
        effect->unk_34;

    frames_left = effect->unk_32.u - 1;
    effect->unk_32.s = frames_left;
    effect->unk_08 = effect->unk_04.at00u.v;
    if ((frames_left << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
