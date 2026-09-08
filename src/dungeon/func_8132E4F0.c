#include "common.h"

typedef struct S_801654F0_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801654F0_0;   /* arg1 in func_801654F0 */

typedef struct S_801654F0_1_pre {
    u16 unk_00;
} S_801654F0_1_pre;   /* the 0x2 bytes before arg0 in func_801654F0, addressed as arg0[-1] */

typedef struct S_801654F0_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0x26];
    u16 unk_32;
} S_801654F0_1;   /* arg0 in func_801654F0 */



extern s32 D_800814A0[3];

/* Advance effect motion, copy its color, and flag expiration when its lifetime ends. */
void func_801654F0(void *effect, S_801654F0_0 *motion)
{
    u16 life_left;

    motion->unk_00 = motion->unk_00 + motion->unk_0C;
    motion->unk_04 = motion->unk_04 + motion->unk_10;
    motion->unk_08 = motion->unk_08 + motion->unk_14;
    ((S_801654F0_1 *)effect)->unk_04.at00.v = ((S_801654F0_1 *)effect)->unk_00;
    ((S_801654F0_1 *)effect)->unk_04.at01.v = ((S_801654F0_1 *)effect)->unk_01;
    ((S_801654F0_1 *)effect)->unk_04.at02.v = ((S_801654F0_1 *)effect)->unk_02;
    life_left = ((S_801654F0_1 *)effect)->unk_32 - 1;
    ((S_801654F0_1 *)effect)->unk_32 = life_left;
    ((S_801654F0_1 *)effect)->unk_08 = ((S_801654F0_1 *)effect)->unk_04.at00u.v;
    if ((life_left << 0x10) <= 0) {
        ((S_801654F0_1_pre *)effect)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
