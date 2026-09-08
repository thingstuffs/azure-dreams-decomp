#include "common.h"

typedef struct S_80170D40_0_pre {
    u16 unk_00;
} S_80170D40_0_pre;   /* the 0x2 bytes before arg0 in func_80170D40, addressed as arg0[-1] */

typedef struct S_80170D40_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x15];
    u16 unk_18;
} S_80170D40_0;   /* arg0 in func_80170D40 */

typedef struct S_80170D40_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80170D40_1;   /* arg2 in func_80170D40 */



extern s32 D_800814A0[3];

/* Fade the primitive color by one step and flag completion when the counter reaches zero. */
void func_80170D40(void *fade_state, void *unused, S_80170D40_1 *primitive)
{
    u16 steps_left;
    u8 red;

    ((S_80170D40_0 *)fade_state)->unk_02 = (u8)(((S_80170D40_0 *)fade_state)->unk_02 - 0x40);
    red = ((S_80170D40_0 *)fade_state)->unk_00 - 0x40;
    ((S_80170D40_0 *)fade_state)->unk_00 = red;
    ((S_80170D40_0 *)fade_state)->unk_01 = (u8)(((S_80170D40_0 *)fade_state)->unk_01 - 0x40);
    primitive->unk_0C = red;
    primitive->unk_0D = ((S_80170D40_0 *)fade_state)->unk_01;
    primitive->unk_0E = ((S_80170D40_0 *)fade_state)->unk_02;
    steps_left = ((S_80170D40_0 *)fade_state)->unk_18 - 1;
    ((S_80170D40_0 *)fade_state)->unk_18 = steps_left;
    if ((steps_left << 0x10) <= 0) {
        ((S_80170D40_0_pre *)fade_state)[-1].unk_00 = (u16)(((S_80170D40_0_pre *)fade_state)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
