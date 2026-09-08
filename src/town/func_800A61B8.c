#include "common.h"

typedef struct S_800A3918_0 {
    u16 unk_00;
    s16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { u16 s; s16 u; } unk_08;   /* accessed as both */
    u8 pad_0A[0x2];
    s16 unk_0C;
    u8 pad_0E[0x4];
    u16 unk_12;
    union { s16 s; u16 u; } unk_14;   /* accessed as both */
    s16 unk_16;
} S_800A3918_0;   /* arg0 in func_800A3918 */

typedef struct S_800A3918_1 {
    u8 pad_00[0x74];
    void * unk_74;
} S_800A3918_1;   /* D_8008274C in func_800A3918 */

typedef struct S_800A3918_2 {
    u8 pad_00[0xD8A];
    union { s16 s; u16 u; } unk_D8A;   /* accessed as both */
} S_800A3918_2;   /* base in func_800A3918 */



extern void *D_8008274C;
extern s32 D_800C5100;

void func_800A3918(S_800A3918_0 *arg0, s32 arg1) {
    s16 state;
    s32 value;
    register u8 *base ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 tmp;
    u16 utmp;

    state = arg0->unk_02;
    if (state == 0) {
        goto state_zero;
    }
    base = (u8 *)0x80100000;
    if (state == 1) {
        goto state_one;
    }
    goto finish;

state_zero:
    if (arg0->unk_0C == 0) {
        value = (s16)(arg0->unk_08.s + 0x1BC0);
        arg0->unk_06 += 2;
        value %= 0x1C00;
    } else {
        value = (s16)(arg0->unk_08.s + 0x1B71);
        arg0->unk_06 += 1;
        value %= 0x1C00;
    }
    arg0->unk_08.u = value;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    arg0->unk_00++;
    if (((S_800A3918_1 *)D_8008274C)->unk_74 == &D_800C5100) {
        arg0->unk_02 = 1;
    }
    goto finish;

state_one:
    ASM_KEEP_NV(base);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    tmp = ((S_800A3918_2 *)base)->unk_D8A.s;
    utmp = ((S_800A3918_2 *)base)->unk_D8A.u;
    if (tmp < -0x1FFF) {
        ((S_800A3918_2 *)base)->unk_D8A.s = -0x2000;
    } else {
        arg0->unk_12 -= 0x20;
        tmp = utmp + arg0->unk_12;
        ((S_800A3918_2 *)base)->unk_D8A.s = tmp;
        if (tmp < -0x1FFF) {
            ((S_800A3918_2 *)base)->unk_D8A.s = -0x2000;
        }
    }
    if (arg0->unk_14.s < 0x200) {
        arg0->unk_14.s = arg0->unk_14.u + 0x20;
    }
    if (arg0->unk_0C == 0) {
        value = (s16)(arg0->unk_08.s + 0x1C00 - arg0->unk_14.u);
        arg0->unk_06 += 2;
        value %= 0x1C00;
    } else {
        value = (s16)(arg0->unk_08.s + 0x1C00 - arg0->unk_14.s * 2);
        arg0->unk_06 += 1;
        value %= 0x1C00;
    }
    arg0->unk_08.u = value;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    arg0->unk_00++;

finish:
    arg0->unk_16 = arg0->unk_08.u / 0x200 + 0x10;
}
