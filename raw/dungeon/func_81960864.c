#include "common.h"

extern void *D_80083160[3];
extern u8 D_801C9E40[16];

extern void func_8002616C();
extern s32 func_8006658C(void *, s32);
extern void func_80067E2C();

void func_81960864(void *arg0, s32 arg1)
{
    s32 temp_s0;
    s32 temp_s0_2;
    register s32 temp_s0_copy ASM_REG("$16");
    s32 temp_s2;
    register void *temp_s1 ASM_REG("$17");
    s32 var_a0;
    s32 var_a0_2;
    void **temp_s5;
    void *ctx;
    void *ctx2;

    ctx = D_80083160[0];
    temp_s5 = D_80083160;
    temp_s0 = *(s32 *)((u8 *)ctx + 0x8D0);
    temp_s1 = (u8 *)ctx + 0x8B0;
    *(s32 *)((u8 *)ctx + 0x8D0) = temp_s0 + 0xC;
    temp_s2 = ctx != (void *)D_801C9E40;
    func_80067E2C(temp_s0, D_80083160[0], ctx);
    {
        register void *call_a0 ASM_REG("$4");
        register s32 call_a1 ASM_REG("$5");

        call_a0 = temp_s1;
        call_a1 = temp_s0;
        ASM_KEEP(call_a0);
        ASM_KEEP(call_a1);
        func_8006658C(call_a0, call_a1);
    }
    temp_s0_copy = temp_s2;
    ASM_KEEP(temp_s0_copy);

    if (arg1 != 0) {
        register s32 temp_v0 ASM_REG("$2");

        temp_v0 = temp_s2;
        ASM_KEEP(temp_v0);
        var_a0 = 0;
        if (temp_v0 != 0) {
            var_a0 = -0xE0;
        }
        func_8002616C(var_a0, arg0, arg1, temp_s1);
    }

    {
        register s32 temp_v0 ASM_REG("$2");

        temp_v0 = temp_s0_copy;
        ASM_KEEP(temp_v0);
        var_a0_2 = 0;
        if (temp_v0 != 0) {
            var_a0_2 = -0xE0;
        }
    }
    func_8002616C(var_a0_2, arg0, 0, temp_s1);

    ctx2 = *temp_s5;
    temp_s0_2 = *(s32 *)((u8 *)ctx2 + 0x8D0);
    *(s32 *)((u8 *)ctx2 + 0x8D0) = temp_s0_2 + 0xC;
    func_80067E2C(temp_s0_2, arg0);
    func_8006658C(temp_s1, temp_s0_2);
}

/* MECHANISM: The 0x30 frame holds s0-s5; D_80083160 stays in s5 and the long-lived OT base in s1.
   Fixed a0/a1 ABI locals move both args before func_8006658C, freeing its delay slot for the disjoint s0=s2 copy.
   Leaving temp_s2 naturally allocated preserves retail's xor-in-v0 followed by sltu-into-s2 sequence. */
