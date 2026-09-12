#include "common.h"


extern s32 D_800814A0[3];
extern s32 D_80083170[3];


typedef struct S_800A5AF0_0_pre {
    u16 unk_00;
} S_800A5AF0_0_pre;   /* the 0x2 bytes before arg0 in func_800A5AF0, addressed as arg0[-1] */

typedef struct S_800A5AF0_0 {
    u8 pad_00[0x4];
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    s16 unk_06;
    s16 unk_08;
} S_800A5AF0_0;   /* arg0 in func_800A5AF0 */

typedef struct S_800A5AF0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800A5AF0_1;   /* arg1 in func_800A5AF0 */

typedef struct S_800A5AF0_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
} S_800A5AF0_2;   /* arg2 in func_800A5AF0 */

/* Interpolate effect values, hold briefly, then fade the colors and mark completion. */
void func_800A5AF0(void *transition, S_800A5AF0_1 *output, S_800A5AF0_2 *appearance) {
    s16 divisor;
    s16 timer;
    s16 state;
    u16 level;
    u16 next_state; /* MATCH: Both arms merge the updated state in retail's $v0. */

    state = ((S_800A5AF0_0 *)transition)->unk_04.s;
    if (state == 0) {
        output->unk_02 = (s16)(
            (u16)output->unk_02 +
            ((s32)(((S_800A5AF0_0 *)transition)->unk_08 - output->unk_02) /
             (s16)((S_800A5AF0_0 *)transition)->unk_06));

        level = appearance->unk_1C;
        divisor = ((S_800A5AF0_0 *)transition)->unk_06;
        appearance->unk_1C =
            (u16)(level + ((s32)(0x1000 - level) / divisor));

        timer = (u16)((S_800A5AF0_0 *)transition)->unk_06 - 1;
        ((S_800A5AF0_0 *)transition)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            ((S_800A5AF0_0 *)transition)->unk_06 = 0x30;
            appearance->unk_1C = 0x1000;
            ((S_800A5AF0_0 *)transition)->unk_04.u = ((S_800A5AF0_0 *)transition)->unk_04.u + 1;
            goto end;
        }
    } else if (state == 1) {
        if (D_80083170[0] != 0) {
            ((S_800A5AF0_0 *)transition)->unk_06 = 0;
        }

        timer = (u16)((S_800A5AF0_0 *)transition)->unk_06 - 1;
        ((S_800A5AF0_0 *)transition)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            next_state = ((S_800A5AF0_0 *)transition)->unk_04.u;

            ((S_800A5AF0_0 *)transition)->unk_06 = 0x20;
            next_state = next_state + 1;
            ((S_800A5AF0_0 *)transition)->unk_04.u = next_state;
            goto end;
        }
    } else {
        appearance->unk_0E = (u8)(
            appearance->unk_0E -
            ((s32)appearance->unk_0E / (s16)((S_800A5AF0_0 *)transition)->unk_06));
        appearance->unk_0D = (u8)(
            appearance->unk_0D -
            ((s32)appearance->unk_0D / (s16)((S_800A5AF0_0 *)transition)->unk_06));
        appearance->unk_0C = (u8)(
            appearance->unk_0C -
            ((s32)appearance->unk_0C / (s16)((S_800A5AF0_0 *)transition)->unk_06));

        timer = (u16)((S_800A5AF0_0 *)transition)->unk_06 - 1;
        ((S_800A5AF0_0 *)transition)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            ((S_800A5AF0_0_pre *)transition)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
end:
}
