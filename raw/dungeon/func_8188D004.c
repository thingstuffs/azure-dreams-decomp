#include "common.h"

typedef s32 M2C_UNK;

M2C_UNK func_8002522C();
void *func_8003FD64();
M2C_UNK func_8004491C();

extern M2C_UNK D_800247AC[3];
extern M2C_UNK D_80024A68[3];

void *func_80024804(s32 arg0, void *arg1, s32 arg2, s32 arg3)
{
    register void *temp_s3 ASM_REG("$19") = arg1;
    register s32 temp_s5 ASM_REG("$21") = arg3;
    register s32 temp_s4 ASM_REG("$20");
    register s32 var_s0 ASM_REG("$16");
    register void *temp_s1 ASM_REG("$17");
    register void *temp_v0 ASM_REG("$18");

    temp_s4 = arg0 - 0x20;
    temp_v0 = func_8003FD64(2, temp_s4);
    if (temp_v0 != 0) {
        *(M2C_UNK **)((u8 *)temp_v0 + 0x10) = D_800247AC;
        func_8004491C(temp_v0, D_80024A68);

        temp_s1 = *(void **)((u8 *)temp_v0 + 8);
        *(u16 *)((u8 *)temp_s1 + 2) = *(u16 *)((u8 *)temp_s3 + 2);
        var_s0 = 0;
        *(u16 *)((u8 *)temp_s1 + 6) = *(u16 *)((u8 *)temp_s3 + 6);
        *(u16 *)((u8 *)temp_s1 + 0xA) = *(u16 *)((u8 *)temp_s3 + 0xA);
        temp_s3 = (void *)temp_s4;
        *(s32 *)((u8 *)temp_v0 + 0x20) = temp_s5;
        ASM_KEEP(temp_s5);

        do {
            func_8002522C(temp_s1, (s16)(var_s0 << 8), 0x40, -0x100, temp_s3);
            var_s0 += 1;
        } while (var_s0 < 0x10);
    }
    return temp_v0;
}

/* MECHANISM: The 0x38 frame holds s3=arg1, s5=arg3, s4=arg0-0x20,
   s2=result, s1=child, and s0=loop index; the fifth call arg uses sp+0x10.
   ASM_KEEP(s5) at its true last use changes sched2 prologue entry order only,
   placing the s5 save/copy between the s3 and s4 packets byte-exactly. */
