#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8008F01C();        /* extern */
M2C_UNK func_8008F104();                         /* extern */
M2C_UNK func_8009B218(); /* extern */
M2C_UNK func_8009C818();     /* extern */
extern M2C_UNK D_800D0690;

typedef struct S_8009C7A8_0 {
    u8 pad_00[0x94];
    u8 unk_94;
} S_8009C7A8_0;   /* arg0 in func_8009C7A8 */

typedef struct S_8009C7A8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8009C7A8_1;   /* arg2 in func_8009C7A8 */

void func_8009C7A8(S_8009C7A8_0 *arg0, M2C_UNK arg1, S_8009C7A8_1 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    if (arg0->unk_94 != 0) {
        arg2->unk_08 = arg4;
        func_8008F104(arg0, arg1, arg5);
        func_8009C818(arg0, arg1, arg2, 0);
        return;
    }
    arg2->unk_08 = arg3;
    func_8008F01C(arg0, arg1, arg5);
    {
        void *call_arg0;
        M2C_UNK call_arg1;
        void *call_arg2;
        M2C_UNK *call_arg3;

        call_arg0 = arg0;
        ASM_KEEP(call_arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        call_arg1 = arg1;
        ASM_KEEP(call_arg1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        call_arg2 = arg2;
        ASM_KEEP(call_arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
        call_arg3 = &D_800D0690;
        ASM_KEEP(call_arg3);   /* MATCH pin: retail schedule: same instructions, different order without it */
        func_8009B218(call_arg0, call_arg1, call_arg2, call_arg3);
    }
}

/* MECHANISM: Correct callee arities naturally hold arg0/arg1/arg2 in s0/s1/s2
   and reproduce the 0x20 frame plus the jump-shaped func_8009C818 tail.
   Guarded block-local a0-a3 carriers fully materialize &D_800D0690 before
   the final jal, preserving retail's nop delay slot. */
