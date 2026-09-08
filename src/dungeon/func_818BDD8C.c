#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_800256A0() __attribute__((noreturn));
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern M2C_UNK D_800254E0;
extern M2C_UNK D_80025DF8;
extern M2C_UNK D_80045340;

typedef struct S_818BDD8C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818BDD8C_0;   /* temp_v0 in func_818BDD8C */

typedef struct S_818BDD8C_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_818BDD8C_1;   /* temp_v1 in func_818BDD8C */

typedef struct S_818BDD8C_2 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_818BDD8C_2;   /* arg0 in func_818BDD8C */

typedef struct S_818BDD8C_3 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818BDD8C_3;   /* temp_s0 in func_818BDD8C */

typedef struct S_818BDD8C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDD8C_4;   /* arg1 in func_818BDD8C */

typedef struct S_818BDD8C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BDD8C_5;   /* temp_v1_4 in func_818BDD8C */

void *func_818BDD8C(S_818BDD8C_2 *arg0, S_818BDD8C_4 *arg1)
{
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 other_flags;
    register s32 temp_v1_2 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_818BDD8C_3 *temp_s0;
    void *temp_v0;
    S_818BDD8C_1 *temp_v1;
    S_818BDD8C_5 *temp_v1_4;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        ((S_818BDD8C_0 *)temp_v0)->unk_10 = &D_800254E0;
        ((S_818BDD8C_0 *)temp_v0)->unk_20 = arg0;
        temp_v1->unk_10 = 0;
        temp_v1->unk_14 =
            (u16)arg0->unk_12;
        temp_s0 = ((S_818BDD8C_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        temp_s0->unk_12 = 0x7E01;
        temp_s0->unk_08 = &D_80025DF8;
        temp_v1_2 = temp_s0->unk_14 | 0xC;
        other_flags = temp_s0->unk_10 | 0x20;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        temp_s0->unk_14 = temp_v1_2;
        temp_v1_2 |= 0x100;
        temp_s0->unk_10 = other_flags;
        temp_s0->unk_14 = temp_v1_2;
        {
            register void *call_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 scale;

            temp_s0->unk_1A =
                (s16)(rand() % 0x1000);
            call_obj = temp_v0;
            scale = 0x400;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            temp_s0->unk_1E = scale;
            temp_s0->unk_1C = scale;
            func_8004491C(call_obj, &D_80045340);
        }
        temp_v1_4 = ((S_818BDD8C_0 *)temp_v0)->unk_08;
        ASM_KEEP(temp_v1_4);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        {
            register void *v0pin ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
            v0pin = temp_v0;
            ASM_KEEP(v0pin);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        }
        temp_a0 = arg1->unk_00;
        temp_a1 = arg1->unk_04;
        temp_a2 = arg1->unk_08;
        temp_a3 = arg1->unk_0C;
        temp_v1_4->unk_00 = temp_a0;
        temp_v1_4->unk_04 = temp_a1;
        temp_v1_4->unk_08 = temp_a2;
        temp_v1_4->unk_0C = temp_a3;
        temp_a0 = arg1->unk_10;
        temp_a1 = arg1->unk_14;
        temp_v1_4->unk_10 = temp_a0;
        temp_v1_4->unk_14 = temp_a1;
        func_800256A0(temp_a0, temp_a1, temp_a2, temp_a3);
    }
    return 0;
}

/* MECHANISM: The natural 0x20 frame holds arg0/object/arg1 in s0/s1/s2.
   A v1 flags accumulator plus a separate v0 flags word prevents OR fusion;
   pinned a0/v0 lifetimes and a fence place li before the callback la pair,
   while the kept destination and v0 result preserve the retail tail ABI. */
