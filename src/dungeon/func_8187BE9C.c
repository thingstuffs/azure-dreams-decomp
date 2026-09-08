#include "common.h"

typedef struct S_8187BE9C_0_pre {
    u16 unk_00;
} S_8187BE9C_0_pre;   /* the 0x2 bytes before arg0 in func_8187BE9C, addressed as arg0[-1] */

typedef struct S_8187BE9C_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    s16 unk_04;
    u8 pad_06[0x30];
    u8 unk_36;
    u8 unk_37;
    u8 unk_38;
    u8 pad_39[0x9];
    s16 unk_42;
    u8 pad_44[0x8];
    u8 unk_4C;
} S_8187BE9C_0;   /* arg0 in func_8187BE9C */

typedef struct S_8187BE9C_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
} S_8187BE9C_1;   /* arg2 in func_8187BE9C */



extern s16 D_8002694C[5];
extern s32 D_800814A0[3];
extern void func_800256EC(void) __attribute__((noreturn));
extern void func_800256F0(void) __attribute__((noreturn));

void func_8187BE9C(void *arg0, s32 arg1, S_8187BE9C_1 *arg2)
{
    s16 state;

    D_8002694C[0] = 1;
    ((S_8187BE9C_0 *)arg0)->unk_02.s--;

    state = ((S_8187BE9C_0 *)arg0)->unk_42;
    if (state == 0) {
        goto state_0;
    }
    if (state == 1) {
        goto state_1;
    }
    func_800256F0();

state_0:
    {
        s32 tail_value;

        ((S_8187BE9C_0 *)arg0)->unk_42 = 1;
        tail_value = ((S_8187BE9C_0 *)arg0)->unk_4C + 24;
        ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_800256EC();
    }

state_1:
    ((S_8187BE9C_0 *)arg0)->unk_42 = 0;
    ((S_8187BE9C_0 *)arg0)->unk_4C -= 24;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    arg2->unk_0C =
        ((S_8187BE9C_0 *)arg0)->unk_36 * ((S_8187BE9C_0 *)arg0)->unk_02.u /
        ((S_8187BE9C_0 *)arg0)->unk_04;
    arg2->unk_0D =
        ((S_8187BE9C_0 *)arg0)->unk_37 * ((S_8187BE9C_0 *)arg0)->unk_02.u /
        ((S_8187BE9C_0 *)arg0)->unk_04;
    arg2->unk_0E =
        ((S_8187BE9C_0 *)arg0)->unk_38 * ((S_8187BE9C_0 *)arg0)->unk_02.u /
        ((S_8187BE9C_0 *)arg0)->unk_04;

    if (((S_8187BE9C_0 *)arg0)->unk_02.u <= 0) {
        ((S_8187BE9C_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    if (arg2->unk_14 & 0x8000) {
        ((S_8187BE9C_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
