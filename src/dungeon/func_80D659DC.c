#include "common.h"
#include "records/Rec_D_800E3D7C.h"



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
} S_80D659DC_9;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80D659DC */


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

/* Spawns an effect offset from the source with randomized velocity biased along the given angle. */
void func_80D659DC(Rec_D_800E3D7C *source, u32 angle, s32 effect_param) {
    S_80D659DC_1 *position_x;
    S_80D659DC_3 *position_y;
    S_80D659DC_4 *velocity_x;
    S_80D659DC_5 *velocity_y;
    S_80D659DC_2 *direction;
    EffectBase *base;
    Effect *effect;

    effect = func_8003FD64(0x211, source);
    if (effect != NULL) {
        base = &effect->base;
        ((S_80D659DC_0 *)effect)->unk_10 = &D_800D707C;
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)effect)->unk_08))->unk_02 = (u16)
            ((S_80D659DC_9 *)(source->unk_08.at00_pv.v))->unk_02;
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)effect)->unk_08))->unk_06 = (u16)
            ((S_80D659DC_9 *)(source->unk_08.at00_pv.v))->unk_06;
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)effect)->unk_08))->unk_0A = (s16)
            (((S_80D659DC_9 *)(source->unk_08.at00_pv.v))->unk_0A - 0x58);
        direction = (void *)D_800E2468 + ((angle >> 7) & 0x1C);
        position_x = ((S_80D659DC_0 *)effect)->unk_08;
        position_x->unk_02 = (u16)
            (position_x->unk_02 +
             (direction->unk_00 * 0x12));
        position_y = ((S_80D659DC_0 *)effect)->unk_08;
        position_y->unk_06 = (u16)
            (position_y->unk_06 +
             (direction->unk_02 * 0x12));
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)effect)->unk_08))->unk_0C = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)effect)->unk_08))->unk_10 = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        ((S_80D659DC_8 *)(((S_80D659DC_6 *)effect)->unk_08))->unk_14 = (s32)
            (((rand() & 0x7FFF) - 0x4000) * 0x10);
        velocity_x = ((S_80D659DC_0 *)effect)->unk_08;
        velocity_x->unk_0C = (s32)
            (velocity_x->unk_0C +
             (direction->unk_00 * 0x1C0000));
        {
            s32 direction_y = direction->unk_02;

            velocity_y = ((S_80D659DC_0 *)effect)->unk_08;
            velocity_y->unk_10 = (s32)
                (velocity_y->unk_10 +
                 (direction_y * 0x1C0000));
            base->field14 = angle;
            base->field32 = 0xC;
            base->field34 = 0xC;
            func_8004491C(effect, &D_800D68F4, velocity_y);
            ((S_80D659DC_0 *)effect)->unk_20 = effect_param;
            base->field8 = effect_param;
        }
    }
}
