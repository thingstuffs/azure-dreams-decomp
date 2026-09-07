#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

typedef struct S_80D659DC_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80D659DC_6;   /* temp_v0 in func_80D659DC */

typedef struct S_80D659DC_7 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80D659DC_7;   /* arg0 in func_80D659DC */

typedef struct S_80D659DC_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80D659DC_8;   /* ((S_80D659DC_6 *)temp_v0)->unk_08 in func_80D659DC */

typedef struct S_80D659DC_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D659DC_9;   /* ((S_80D659DC_7 *)arg0)->unk_08 in func_80D659DC */


typedef struct EffectBase {
    u8 pad0[8];
    s32 field8;
    u8 padC[8];
    u16 field14;
    u8 pad16[0x1C];
    s16 field32;
    s16 field34;
} EffectBase;

typedef struct Effect {
    u8 pad0[0x20];
    EffectBase base;
} Effect;

extern void *func_8003FD64();
extern M2C_UNK func_8004491C();
extern s32 rand();
extern s32 D_800D68F4[];
extern s32 D_800D707C[];
extern s16 D_800E2468[];

typedef struct S_80D659DC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80D659DC_0;   /* temp_v0 in func_80D659DC */

typedef struct S_80D659DC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80D659DC_1;   /* temp_a0 in func_80D659DC */

typedef struct S_80D659DC_2 {
    s16 unk_00;
    s16 unk_02;
} S_80D659DC_2;   /* temp_s0 in func_80D659DC */

typedef struct S_80D659DC_3 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_80D659DC_3;   /* temp_a0_2 in func_80D659DC */

typedef struct S_80D659DC_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80D659DC_4;   /* temp_a1 in func_80D659DC */

typedef struct S_80D659DC_5 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80D659DC_5;   /* temp_a2 in func_80D659DC */

void func_80D659DC(S_80D659DC_7 *arg0, u32 arg1, s32 arg2) {
    S_80D659DC_1 *temp_a0;
    S_80D659DC_3 *temp_a0_2;
    S_80D659DC_4 *temp_a1;
    S_80D659DC_5 *temp_a2;
    S_80D659DC_2 *temp_s0;
    EffectBase *temp_s0_2;
    Effect *temp_v0;

    temp_v0 = func_8003FD64(0x211, arg0);
    if (temp_v0 != NULL) {
        temp_s0_2 = &temp_v0->base;
        ((S_80D659DC_0 *)temp_v0)->unk_10 = &D_800D707C;
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)temp_v0)->unk_08))->unk_02 = (u16)
            ((S_80D659DC_9 *)(arg0->unk_08))->unk_02;
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)temp_v0)->unk_08))->unk_06 = (u16)
            ((S_80D659DC_9 *)(arg0->unk_08))->unk_06;
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)temp_v0)->unk_08))->unk_0A = (s16)
            (((S_80D659DC_9 *)(arg0->unk_08))->unk_0A - 0x58);
        temp_s0 = (void *)D_800E2468 + ((arg1 >> 7) & 0x1C);
        temp_a0 = ((S_80D659DC_0 *)temp_v0)->unk_08;
        temp_a0->unk_02 = (u16)
            (temp_a0->unk_02 +
             (temp_s0->unk_00 * 0x12));
        temp_a0_2 = ((S_80D659DC_0 *)temp_v0)->unk_08;
        temp_a0_2->unk_06 = (u16)
            (temp_a0_2->unk_06 +
             (temp_s0->unk_02 * 0x12));
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)temp_v0)->unk_08))->unk_0C = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)temp_v0)->unk_08))->unk_10 = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)temp_v0)->unk_08))->unk_14 = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        temp_a1 = ((S_80D659DC_0 *)temp_v0)->unk_08;
        temp_a1->unk_0C = (s32)
            (temp_a1->unk_0C +
             (temp_s0->unk_00 * 0x1C0000));
        {
            s32 temp_v1 = temp_s0->unk_02;

            temp_a2 = ((S_80D659DC_0 *)temp_v0)->unk_08;
            temp_a2->unk_10 = (s32)
                (temp_a2->unk_10 +
                 (temp_v1 * 0x1C0000));
            temp_s0_2->field14 = arg1;
            temp_s0_2->field32 = 0xC;
            temp_s0_2->field34 = 0xC;
            func_8004491C(temp_v0, &D_800D68F4, temp_a2);
            ((S_80D659DC_0 *)temp_v0)->unk_20 = arg2;
            temp_s0_2->field8 = arg2;
        }
    }
}
