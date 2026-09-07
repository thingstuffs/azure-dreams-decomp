#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

typedef struct S_80D65810_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    u8 pad_10[0x1C];
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
} S_80D65810_0;   /* temp_s0 in func_80D65810 */

typedef struct S_80D65810_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D65810_1;   /* temp_v0 in func_80D65810 */

typedef struct S_80D65810_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x8];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80D65810_2;   /* temp_a0 in func_80D65810 */

typedef struct S_80D65810_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D65810_3;   /* temp_s1 in func_80D65810 */

typedef struct S_80D65810_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D65810_4;   /* input in func_80D65810 */

typedef struct S_80D65810_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80D65810_5;   /* temp_a0_2 in func_80D65810 */


M2C_UNK func_8003DB94();
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 rand();
extern u8 D_800DE870[];
extern void func_80045340(void);
extern void func_80170D34(void);

void func_80D65810(s32 arg0, void *arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5) {
    u16 temp_v0_2;
    S_80D65810_4 *input;
    u16 x;
    register s32 y ASM_REG("$20");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    register s32 z ASM_REG("$21");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    s32 size;
    S_80D65810_2 *temp_a0;
    S_80D65810_5 *temp_a0_2;
    S_80D65810_0 *temp_s0;
    S_80D65810_3 *temp_s1;
    void *temp_v0;

    input = arg1;
    x = arg3;
    y = arg4;
    z = arg5;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_0C = 0x1E;
        temp_s0->unk_0E = 0x1E;
        ((S_80D65810_1 *)temp_v0)->unk_10 = func_80170D34;
        func_8004491C(temp_v0, func_80045340);
        temp_a0 = ((S_80D65810_1 *)temp_v0)->unk_0C;
        temp_a0->unk_06 = 0;
        temp_a0->unk_14 |= 0xC;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_v0_2 = temp_a0->unk_14;
        ASM_KEEP(temp_v0_2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        size = 0x60;
        ASM_KEEP(size);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        temp_a0->unk_10 = size;
        temp_a0->unk_14 = (u16)(temp_v0_2 | 2);
        temp_s1 = ((S_80D65810_1 *)temp_v0)->unk_08;
        temp_s1->unk_00.at02.v = x;
        temp_s1->unk_04.at02.v = (u16)y;
        temp_s1->unk_0A = (u16)z;
        temp_s0->unk_34 = 0x40000;
        temp_s0->unk_40 = 0x8000;
        temp_s0->unk_2C = (s32)((s32)temp_s1->unk_00.at00.v >> 1);
        temp_s0->unk_30 = (s32)((s32)temp_s1->unk_04.at00.v >> 1);
        if (temp_s0->unk_2C == 0) {
            temp_s0->unk_2C = (s32)(((rand(temp_a0) & 0x1F) - 0x10) << 0xF);
            temp_s0->unk_30 = (s32)(((rand() & 0x1F) - 0x10) << 0xF);
        }
        temp_s0->unk_38 = (s32)(0 - ((s32)temp_s0->unk_2C >> 4));
        temp_s0->unk_3C = (s32)(0 - ((s32)temp_s0->unk_30 >> 4));
        temp_s1->unk_00.at02.v = (u16)(temp_s1->unk_00.at02.v + input->unk_02);
        temp_s1->unk_04.at02.v = (u16)(temp_s1->unk_04.at02.v + input->unk_06);
        temp_s1->unk_0A = (u16)(temp_s1->unk_0A + input->unk_0A);
        temp_a0_2 = ((S_80D65810_1 *)temp_v0)->unk_0C;
        temp_a0_2->unk_1C = 0xC00;
        temp_a0_2->unk_1E = 0xC00;
        temp_a0_2->unk_0E = 0x80;
        temp_a0_2->unk_0D = 0x80;
        temp_a0_2->unk_0C = 0x80;
        temp_a0_2->unk_12 = 0x7DCF;
        temp_a0_2->unk_14 = (u16)(temp_a0_2->unk_14 | 0x100);
        func_8003DB94(temp_a0_2, D_800DE870, 0);
    }
}

/* MECHANISM: Inherited pins preserve the retail 0x30 frame and s4/s5 argument holds.
   Splitting the flags RMW around ASM_SCHED_BARRIER makes its sh precede the reused-value copy.
   Guarded s0/s1 pins restore the held object/subobject bases perturbed by that zero-word fence. */
