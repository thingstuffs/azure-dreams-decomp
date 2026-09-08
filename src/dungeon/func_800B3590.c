#include "common.h"

typedef struct S_800B8CF0_0_pre {
    u16 unk_00;
} S_800B8CF0_0_pre;   /* the 0x2 bytes before arg0 in func_800B8CF0, addressed as arg0[-1] */

typedef struct S_800B8CF0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B8CF0_0;   /* arg0 in func_800B8CF0 */

typedef struct S_800B8CF0_1 {
    u8 pad_00[0xC];
    union { struct { s8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; s8 v; } at01; struct { u8 pad[0x2]; s8 v; } at02; } unk_0C;   /* overlapping accesses */
} S_800B8CF0_1;   /* arg2 in func_800B8CF0 */



extern s32 D_800814A0; /* overlays/dungeon/first_pass_matched/func_800AB5D4.c */

/* Count down the effect, alternating its shade until marking it finished. */
void func_800B8CF0(void *state, s32 unused, void *primitive) {
    s32 ticks_left;

    ticks_left = ((S_800B8CF0_0 *)state)->unk_02 - 1;
    ((S_800B8CF0_0 *)state)->unk_02 = (u16) ticks_left;
    if (((ticks_left << 16) >> 16) <= 0) {
        (*(u16 *)((u8 *)state + -2)) = (u16) (((S_800B8CF0_0_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0 |= 0x8000;
        return;
    }
    if (ticks_left & 1) {
        s8 shade = (s8) ((((ticks_left << 16) >> 16) << 3) | 0x20);
        ((S_800B8CF0_1 *)primitive)->unk_0C.at00.v = shade;
        ((S_800B8CF0_1 *)primitive)->unk_0C.at02.v = shade;
        ((S_800B8CF0_1 *)primitive)->unk_0C.at01.v = shade;
        return;
    }
    ((S_800B8CF0_1 *)primitive)->unk_0C.at00u.v = 0x00101010;
}
