#include "common.h"
#include "m2c_compat.h"

typedef struct Copy12 {
    M2C_UNK word[3];
} __attribute__((packed)) Copy12;

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
s32 func_80167088();                         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_80165AB8;
extern M2C_UNK D_80173B34[3];


typedef struct S_80165D0C_0 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80165D0C_0;   /* arg0 in func_80165D0C */

typedef struct S_80165D0C_1 {
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
    u8 pad_48[0x18];
    s32 unk_60;
} S_80165D0C_1;   /* temp_s1 in func_80165D0C */

typedef struct S_80165D0C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80165D0C_2;   /* temp_s0 in func_80165D0C */

typedef struct S_80165D0C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80165D0C_3;   /* (*(void **)((u8 *)temp_v0 + 8)) in func_80165D0C */

typedef struct S_80165D0C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80165D0C_4;   /* ((S_80165D0C_0 *)arg0)->unk_08 in func_80165D0C */

void func_80165D0C(S_80165D0C_0 *arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_v1;
    S_80165D0C_2 *temp_s0;
    S_80165D0C_1 *temp_s1;
    void *temp_v0;
    register s32 held_arg4 ASM_REG("$19") = arg4;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 held_arg5 ASM_REG("$20") = arg5;   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    temp_v0 = func_8003FC64(0x12);
    if (temp_v0 != NULL) {
        (*(M2C_UNK **)((u8 *)temp_v0 + 0x10)) = &D_80165AB8;
        ((S_80165D0C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_02 = (s16) (((S_80165D0C_4 *)(arg0->unk_08))->unk_02 + arg3);
        ((S_80165D0C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_06 = (s16) (((S_80165D0C_4 *)(arg0->unk_08))->unk_06 + held_arg4);
        ((S_80165D0C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_0A = (s16) (((S_80165D0C_4 *)(arg0->unk_08))->unk_0A + held_arg5);
        temp_s1 = temp_v0 + 0x20;
        temp_s1->unk_42 = (u16) ((S_80165D0C_4 *)(arg0->unk_08))->unk_02;
        temp_s1->unk_44 = (u16) ((S_80165D0C_4 *)(arg0->unk_08))->unk_06;
        temp_s1->unk_46 = (u16) ((S_80165D0C_4 *)(arg0->unk_08))->unk_0A;
        ((S_80165D0C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) * 8);
        ((S_80165D0C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) * 8);
        ((S_80165D0C_3 *)((*(void **)((u8 *)temp_v0 + 8))))->unk_14 = (s32) (arg6 + 0xFFFC0000);
        temp_s1->unk_60 = 0x10000;
        temp_s1->unk_14 = arg1;
        temp_s1->unk_32 = 0;
        temp_s1->unk_34 = 0;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0 = (*(void **)((u8 *)temp_v0 + 0xC));
        temp_s0->unk_06 = -4;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 & 0xFFF3);
        temp_v1 = 0x1000 / (s32) (func_80167088(5) + 8);
        temp_s0->unk_0C = arg2;
        temp_s0->unk_1E = (s16) temp_v1;
        temp_s0->unk_1C = (s16) temp_v1;
        (*(s32 *)((u8 *)temp_v0 + 0x20)) = arg2;
        temp_s1->unk_04 = arg2;
        temp_s1->unk_08 = arg2;
        (*(Copy12 *)((u8 *)temp_v0 + 0x56)) =
            (*(Copy12 *)((u8 *)D_80173B34 + 0));
        temp_s0->unk_08 = (void *) (temp_v0 + 0x56);
    }
}

/* MECHANISM: Pinned stack args arg4/arg5 create the retail s3/s4 hold set and 0x30 frame;
   end-placed ASM_KEEP guards preserve the exact prologue and call-delay scheduling.
   A packed Copy12 assignment emits the retail lwl/lwr and swl/swr copy sequence. */
