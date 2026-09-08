#include "common.h"

typedef struct S_8181B078_0_pre {
    u16 unk_00;
} S_8181B078_0_pre;   /* the 0x2 bytes before arg0 in func_8181B078, addressed as arg0[-1] */

typedef struct S_8181B078_0 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x18];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x37];
    s32 unk_60;
} S_8181B078_0;   /* arg0 in func_8181B078 */

typedef struct S_8181B078_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8181B078_1;   /* arg1 in func_8181B078 */

typedef struct S_8181B078_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8181B078_2;   /* arg2 in func_8181B078 */



extern s16 D_80025914;
extern s32 D_800814A0[3];

extern void func_8002491C(void) __attribute__((noreturn));
extern void func_80024920(void) __attribute__((noreturn));

void func_8181B078(void *arg0, S_8181B078_1 *arg1, S_8181B078_2 *arg2)
{
    s32 one;
    register s32 tail_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s16 state;

    D_80025914 = 1;
    ((S_8181B078_0 *)arg0)->unk_02.s--;

    if (++((S_8181B078_0 *)arg0)->unk_1C >= 2) {
        ((S_8181B078_0 *)arg0)->unk_1C = 0;
        state = ((S_8181B078_0 *)arg0)->unk_1E;
        one = 1;

        if (state == one) {
            goto state_1;
        }
        if (state >= 2) {
            goto check_state_2;
        }
        if (state == 0) {
            goto state_0;
        }
        func_80024920();

check_state_2:
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
        if (state == 2) {
            goto state_2;
        }
        func_80024920();

state_0:
        ((S_8181B078_0 *)arg0)->unk_1E = one;
        tail_value = ((S_8181B078_0 *)arg0)->unk_28 + 8;
        ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_8002491C();

state_1:
        ((S_8181B078_0 *)arg0)->unk_1E = 2;
        tail_value = ((S_8181B078_0 *)arg0)->unk_28 + 8;
        ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_8002491C();

state_2:
        ((S_8181B078_0 *)arg0)->unk_1E = 0;
        ((S_8181B078_0 *)arg0)->unk_28 -= 16;
    }

    arg1->unk_08 += ((S_8181B078_0 *)arg0)->unk_60;

    if (((S_8181B078_0 *)arg0)->unk_02.u <= 0) {
        ((S_8181B078_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    if (arg2->unk_14 & 0x8000) {
        ((S_8181B078_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
