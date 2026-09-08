#include "common.h"

typedef struct S_800BB030_0_pre {
    u16 unk_00;
} S_800BB030_0_pre;   /* the 0x2 bytes before arg0 in func_800BB030, addressed as arg0[-1] */

typedef struct S_800BB030_0 {
    u8 pad_00[0x66];
    s16 unk_66;
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x2];
    union { u16 s; s16 u; } unk_6C;   /* accessed as both */
    u8 pad_6E[0x29];
    s8 unk_97;
    s8 * unk_98;
} S_800BB030_0;   /* arg0 in func_800BB030 */



extern s32 func_8009CFE0(void);
extern s32 D_800814A0[];

void func_800BB030(void *arg0) {
    s8 *ptr;
    s32 state;
    s32 counter;
    s32 quotient;
    register s32 intensity ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    if (func_8009CFE0() != 0) {
        ptr = ((S_800BB030_0 *)arg0)->unk_98;
        if (ptr != 0) {
            *ptr = 0;
        }
        ((S_800BB030_0_pre *)arg0)[-1].unk_00 |= 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
        goto end;
    }

    counter = ((S_800BB030_0 *)arg0)->unk_6C.s + 1;
    state = ((S_800BB030_0 *)arg0)->unk_68.s;
    ((S_800BB030_0 *)arg0)->unk_6C.s = counter;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    quotient = (s16)counter / 4;
    ((S_800BB030_0 *)arg0)->unk_66 = quotient * 3;
    intensity = (s16)((S_800BB030_0 *)arg0)->unk_6C.s / 2;
    ((S_800BB030_0 *)arg0)->unk_97 = intensity;
    if (((S_800BB030_0 *)arg0)->unk_6C.u < 0x40) {
        goto end;
    }
    ((S_800BB030_0 *)arg0)->unk_6C.s = 0;
    ((S_800BB030_0 *)arg0)->unk_68.u++;
    goto end;

state_1: {
    s32 q;

    q = (s16)counter / 4;
    ((S_800BB030_0 *)arg0)->unk_66 = 0x30 - q * 3;
    ((S_800BB030_0 *)arg0)->unk_97 = 0x20;
    if (((S_800BB030_0 *)arg0)->unk_6C.u >= 0x40) {
        ((S_800BB030_0 *)arg0)->unk_6C.s = 0;
        ((S_800BB030_0 *)arg0)->unk_68.u++;
    }
    goto end;
}

state_2: {
    register s32 half ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    quotient = (s16)counter / 4;
    ((S_800BB030_0 *)arg0)->unk_66 = quotient * 3;
    half = (s16)((S_800BB030_0 *)arg0)->unk_6C.s / 2;
    intensity = 0x20 - half;
    ((S_800BB030_0 *)arg0)->unk_97 = intensity;
    if (((S_800BB030_0 *)arg0)->unk_6C.u < 0x40) {
        goto end;
    }
    ((S_800BB030_0 *)arg0)->unk_6C.s = 0;
    ((S_800BB030_0 *)arg0)->unk_68.u++;
    goto end;
}

state_3: {
    s32 q;

    q = (s16)counter / 4;
    ((S_800BB030_0 *)arg0)->unk_66 = 0x30 - q * 3;
    ((S_800BB030_0 *)arg0)->unk_97 = 0;
    if (((S_800BB030_0 *)arg0)->unk_6C.u < 0x40) {
        goto end;
    }
    ((S_800BB030_0 *)arg0)->unk_6C.s = 0;
    ((S_800BB030_0 *)arg0)->unk_68.s = 0;
}

end:
    return;
}
