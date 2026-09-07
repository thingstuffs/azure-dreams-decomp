/* row func_80024C80 -- exemplar-seeded from landed func_8188D004
 * (MATCH @2.7.2, gate_verified). Opcode-sequence similarity 0.9483.
 * Adaptations read off the retail stream: two data symbols, one callee,
 * and an extra u16 counter increment on D_80026324 that gcc schedules
 * around the func_8004491C delay slot.
 * Ordinary code: no alias, no section attribute, no literal word arrays.
 */
#include "common.h"

typedef s32 M2C_UNK;

M2C_UNK func_8002569C();
void *func_8003FD64();
M2C_UNK func_8004491C();

extern M2C_UNK D_80024804[3];
extern u16 D_80026324;
extern M2C_UNK D_80024EF4[3];

void *func_80024C80(s32 arg0, void *arg1, s32 arg2, s32 arg3)
{
    void *temp_s3 = arg1;
    register s32 temp_s5 ASM_REG("$21") = arg3;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s32 temp_s4;
    s32 var_s0;
    void *temp_s1;
    void *temp_v0;
    u16 counter;

    temp_s4 = arg0 - 0x20;
    temp_v0 = func_8003FD64(2, temp_s4);
    if (temp_v0 != 0) {
        counter = D_80026324;
        *(M2C_UNK **)((u8 *)temp_v0 + 0x10) = D_80024804;
        D_80026324 = counter + 1;
        func_8004491C(temp_v0, D_80024EF4);

        temp_s1 = *(void **)((u8 *)temp_v0 + 8);
        *(u16 *)((u8 *)temp_s1 + 2) = *(u16 *)((u8 *)temp_s3 + 2);
        var_s0 = 0;
        *(u16 *)((u8 *)temp_s1 + 6) = *(u16 *)((u8 *)temp_s3 + 6);
        *(u16 *)((u8 *)temp_s1 + 0xA) = *(u16 *)((u8 *)temp_s3 + 0xA);
        temp_s3 = (void *)temp_s4;
        *(s32 *)((u8 *)temp_v0 + 0x20) = temp_s5;
        ASM_KEEP(temp_s5);   /* MATCH pin: retail schedule: same instructions, different order without it */

        do {
            func_8002569C(temp_s1, (s16)(var_s0 << 8), 0x40, -0x100, temp_s3);
            var_s0 += 1;
        } while (var_s0 < 0x10);
    }
    return temp_v0;
}

/* MECHANISM: The 0x38 frame holds s3=arg1, s5=arg3, s4=arg0-0x20,
   s2=result, s1=child, and s0=loop index; the fifth call arg uses sp+0x10.
   ASM_KEEP(s5) at its true last use changes sched2 prologue entry order only,
   placing the s5 save/copy between the s3 and s4 packets byte-exactly. */
