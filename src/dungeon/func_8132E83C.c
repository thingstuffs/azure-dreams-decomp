#include "common.h"
#include "m2c_compat.h"

typedef struct Copy12 {
    M2C_UNK word[3];
} __attribute__((packed)) Copy12;

void *func_8003FC64(s32);
void func_8004491C(void *, void *);
s32 rand(void);
extern u8 D_80045340;
extern u8 D_801654F0[];
extern M2C_UNK D_80173B34[3];


typedef struct S_8016583C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8016583C_0;   /* arg0 in func_8016583C */

typedef struct S_8016583C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xC];
    u16 unk_42;
    u16 unk_44;
    u16 unk_46;
} S_8016583C_1;   /* temp_s0 in func_8016583C */

typedef struct S_8016583C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8016583C_2;   /* temp_a0 in func_8016583C */

typedef struct S_8016583C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8016583C_3;   /* (*(void **)((u8 *)temp_v0 + 8)) in func_8016583C */

typedef struct S_8016583C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016583C_4;   /* ((S_8016583C_0 *)arg0)->unk_08 in func_8016583C */

void func_8016583C(S_8016583C_0 *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    S_8016583C_2 *temp_a0;
    S_8016583C_1 *temp_s0;
    void *temp_v0;
    register s16 arg1_hold ASM_REG("$22") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 arg2_hold ASM_REG("$21") = arg2;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 arg4_hold = arg4;
    register s32 arg3_hold ASM_REG("$16") = arg3;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 arg5_hold = arg5;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = &D_801654F0;
        ((S_8016583C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_02 = (s16) (((S_8016583C_4 *)(arg0->unk_08))->unk_02 + arg3_hold);
        ASM_KEEP(arg3_hold);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ((S_8016583C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_06 = (s16) (((S_8016583C_4 *)(arg0->unk_08))->unk_06 + arg4_hold);
        ((S_8016583C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_0A = (s16) (((S_8016583C_4 *)(arg0->unk_08))->unk_0A + arg5_hold);
        temp_s0 = temp_v0 + 0x20;
        temp_s0->unk_42 = (u16) ((S_8016583C_4 *)(arg0->unk_08))->unk_02;
        temp_s0->unk_44 = (u16) ((S_8016583C_4 *)(arg0->unk_08))->unk_06;
        temp_s0->unk_46 = (u16) ((S_8016583C_4 *)(arg0->unk_08))->unk_0A;
        ((S_8016583C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_8016583C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_8016583C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_14 = arg6;
        temp_s0->unk_14 = arg1_hold;
        temp_s0->unk_32 = 8;
        temp_s0->unk_34 = 8;
        func_8004491C(temp_v0, &D_80045340);
        temp_a0 = (*(void **)((u8 *)temp_v0 + 0xC));
        temp_a0->unk_1E = 0x200;
        temp_a0->unk_1C = 0x200;
        temp_a0->unk_0C = arg2_hold;
        temp_a0->unk_14 = (u16) (temp_a0->unk_14 & 0xFFF3);
        (*(s32 *)((u8 *)temp_v0 + 0x20)) = arg2_hold;
        temp_s0->unk_04 = arg2_hold;
        temp_s0->unk_08 = arg2_hold;
        (*(Copy12 *)((u8 *)temp_v0 + 0x56)) =
            (*(Copy12 *)((u8 *)D_80173B34 + 0));
        temp_a0->unk_08 = (void *) (temp_v0 + 0x56);
        ASM_KEEP(arg1_hold);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(arg2_hold);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        ASM_KEEP(arg4_hold);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(arg5_hold);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    }
}

/* MECHANISM: Explicit s0/s3-s6 argument roles reproduce the 0x30 frame, save order,
   and held stack-argument lifetimes at the true-space func_8016583C entry.
   One packed 12-byte assignment emits the retail lwl/lwr plus swl/swr copy sequence. */
