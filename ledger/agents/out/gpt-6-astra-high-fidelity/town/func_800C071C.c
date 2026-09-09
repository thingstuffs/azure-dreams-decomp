#include "common.h"

typedef struct S_800BDE7C_0 {
    u8 pad_00[0x68];
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x36];
    s32 * unk_A0;
} S_800BDE7C_0;   /* arg0 in func_800BDE7C */

typedef struct S_800BDE7C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800BDE7C_1;   /* arg2 in func_800BDE7C */



s32 func_800352FC(S_800BDE7C_0 *, s32, S_800BDE7C_1 *, s32);
s32 func_800C2AB4(void *);

void func_800BDE7C(S_800BDE7C_0 *arg0, s32 arg1, S_800BDE7C_1 *arg2, s32 arg3)
{
    s16 state;
    /* MATCH: Preserve retail's source register after making call arguments explicit. */
    register s32 *source ASM_REG("$17");
    /* MATCH: Keep incoming call arguments in their ABI registers across dispatch. */
    register S_800BDE7C_0 *call_arg0 ASM_REG("$4") = arg0;
    register S_800BDE7C_1 *call_arg2 ASM_REG("$6") = arg2;

    state = arg0->unk_68.s;
    source = arg0->unk_A0;

    if (state == 1) {
        goto state_1_or_3;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_1_or_3;
    }
    goto done;

state_0:
    if (func_800352FC(call_arg0, arg1, call_arg2, arg3) == 0) {
        goto done;
    }
    if (func_800C2AB4(arg0) == 0) {
        goto done;
    }
    arg2->unk_08 = source[1];
    goto increment;

state_1_or_3:
    if ((func_800352FC(call_arg0, arg1, call_arg2, arg3) == 0) || (func_800C2AB4(arg0) == 0)) {
        arg0->unk_68.u = (arg0->unk_68.u + 1) & 3;
    }
    goto done;

state_2:
    if (func_800352FC(call_arg0, arg1, call_arg2, arg3) == 0) {
        goto done;
    }
    if (func_800C2AB4(arg0) == 0) {
        goto done;
    }
    arg2->unk_08 = source[0];

increment:
    arg0->unk_68.u = arg0->unk_68.u + 1;

done:
    return;
}

/* MECHANISM: The third ABI argument is kept live in s2, with arg0/source held in s0/s1,
   producing the retail 0x20 frame and save order. Explicit state labels preserve the
   retail dispatch and shared increment blocks; state 1/3 alone applies the modulo mask. */
