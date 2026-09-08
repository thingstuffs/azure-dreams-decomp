#include "common.h"


extern void func_800A5BC4(void) __attribute__((noreturn));
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

void func_800A5AF0(void *arg0, S_800A5AF0_1 *arg1, S_800A5AF0_2 *arg2) {
    s16 divisor;
    s16 timer;
    s16 state;
    u16 value;

    state = ((S_800A5AF0_0 *)arg0)->unk_04.s;
    if (state == 0) {
        arg1->unk_02 = (s16)(
            (u16)arg1->unk_02 +
            ((s32)(((S_800A5AF0_0 *)arg0)->unk_08 - arg1->unk_02) /
             (s16)((S_800A5AF0_0 *)arg0)->unk_06));

        value = arg2->unk_1C;
        divisor = ((S_800A5AF0_0 *)arg0)->unk_06;
        arg2->unk_1C =
            (u16)(value + ((s32)(0x1000 - value) / divisor));

        timer = (u16)((S_800A5AF0_0 *)arg0)->unk_06 - 1;
        ((S_800A5AF0_0 *)arg0)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            u16 next_state;

            ((S_800A5AF0_0 *)arg0)->unk_06 = 0x30;
            arg2->unk_1C = 0x1000;
            next_state = ((S_800A5AF0_0 *)arg0)->unk_04.u + 1;
            ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            func_800A5BC4();
        }
    } else if (state == 1) {
        if (D_80083170[0] != 0) {
            ((S_800A5AF0_0 *)arg0)->unk_06 = 0;
        }

        timer = (u16)((S_800A5AF0_0 *)arg0)->unk_06 - 1;
        ((S_800A5AF0_0 *)arg0)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            u16 next_state = ((S_800A5AF0_0 *)arg0)->unk_04.u;

            ((S_800A5AF0_0 *)arg0)->unk_06 = 0x20;
            ((S_800A5AF0_0 *)arg0)->unk_04.u = next_state + 1;
            return;
        }
    } else {
        arg2->unk_0E = (u8)(
            arg2->unk_0E -
            ((s32)arg2->unk_0E / (s16)((S_800A5AF0_0 *)arg0)->unk_06));
        arg2->unk_0D = (u8)(
            arg2->unk_0D -
            ((s32)arg2->unk_0D / (s16)((S_800A5AF0_0 *)arg0)->unk_06));
        arg2->unk_0C = (u8)(
            arg2->unk_0C -
            ((s32)arg2->unk_0C / (s16)((S_800A5AF0_0 *)arg0)->unk_06));

        timer = (u16)((S_800A5AF0_0 *)arg0)->unk_06 - 1;
        ((S_800A5AF0_0 *)arg0)->unk_06 = timer;
        if ((timer << 16) <= 0) {
            ((S_800A5AF0_0_pre *)arg0)[-1].unk_00 |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }
}

/* MECHANISM: Both callees are zero-argument noreturn continuations, allowing LEAD 19
   to erase the false RA-only frame. The first tail holds state+1 in $v0, and
   ASM_TAILSLOT_PIN sinks its addiu into the tail-j delay slot; the second is natural. */
