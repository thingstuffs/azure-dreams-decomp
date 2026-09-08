#include "common.h"

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
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    union { s16 s; u16 u; } unk_32;   /* accessed as both */
    s16 unk_34;
} S_800D6804_1;   /* arg0 in func_800D6804 */



extern s32 D_800814A0;

/* Advance the state with a decaying delta and fade the effect color until its timer expires. */
void func_800D6804(void *effect, void *state_data)
{
    s16 frames_left;

    {
        register void *state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        register s32 delta ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 scaled_delta;
        register s32 delta_copy ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        s32 accumulated;
        s32 decayed_delta;

        state = state_data;
        delta = ((S_800D6804_0 *)state)->unk_14;
        accumulated = ((S_800D6804_0 *)state)->unk_08;
        scaled_delta = delta << 1;
        delta_copy = delta;
        ASM_KEEP(delta_copy);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        scaled_delta += delta;
        accumulated += delta_copy;
        ((S_800D6804_0 *)state)->unk_08 = accumulated;
        if (scaled_delta < 0) {
            scaled_delta += 3;
        }
        decayed_delta = scaled_delta >> 2;
        ((S_800D6804_0 *)state)->unk_14 = decayed_delta;
    }

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
        D_800814A0 |= 0x8000;
    }
}
