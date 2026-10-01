#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800D6804_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800D6804_0;   /* state in func_800D6804 */

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
} S_800D6804_1;   /* arg0 in func_800D6804 */


static __inline__ void decay_step(S_800D6804_0 *s)
{
    s->unk_08 += s->unk_14;
    s->unk_14 = s->unk_14 * 3 / 4;
}

/* Advance the state with a decaying delta and fade the effect color until its timer expires. */
void func_800D6804(void *effect, void *state_data)
{
    s16 frames_left;

    decay_step((S_800D6804_0 *)state_data);

    ((S_800D6804_1 *)effect)->unk_04.at00.v =
        (((S_800D6804_1 *)effect)->unk_00 * ((S_800D6804_1 *)effect)->unk_32.s) /
        ((S_800D6804_1 *)effect)->unk_34;
    ((S_800D6804_1 *)effect)->unk_04.at01.v =
        (((S_800D6804_1 *)effect)->unk_01 * ((S_800D6804_1 *)effect)->unk_32.s) /
        ((S_800D6804_1 *)effect)->unk_34;
    ((S_800D6804_1 *)effect)->unk_04.at02.v =
        (((S_800D6804_1 *)effect)->unk_02 * ((S_800D6804_1 *)effect)->unk_32.s) /
        ((S_800D6804_1 *)effect)->unk_34;

    frames_left = ((S_800D6804_1 *)effect)->unk_32.u - 1;
    ((S_800D6804_1 *)effect)->unk_32.s = frames_left;
    ((S_800D6804_1 *)effect)->unk_08 = ((S_800D6804_1 *)effect)->unk_04.at00u.v;
    if ((frames_left << 16) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
