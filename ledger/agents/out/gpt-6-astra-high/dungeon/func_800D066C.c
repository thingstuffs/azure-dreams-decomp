#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800D5DCC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800D5DCC_0;   /* temp_v0 in func_800D5DCC */

typedef struct S_800D5DCC_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800D5DCC_1;   /* arg0 in func_800D5DCC */

typedef struct S_800D5DCC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800D5DCC_2;   /* temp_a0 in func_800D5DCC */

typedef struct S_800D5DCC_3 {
    s16 unk_00;
    s16 unk_02;
} S_800D5DCC_3;   /* temp_s0 in func_800D5DCC */

typedef struct S_800D5DCC_4 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800D5DCC_4;   /* temp_a0_2 in func_800D5DCC */

typedef struct S_800D5DCC_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800D5DCC_5;   /* temp_a1 in func_800D5DCC */

typedef struct S_800D5DCC_6 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800D5DCC_6;   /* temp_a2 in func_800D5DCC */

typedef struct S_800D5DCC_7 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
} S_800D5DCC_7;   /* temp_s0_2 in func_800D5DCC */

typedef struct S_800D5DCC_8 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D5DCC_8;   /* ((S_800D5DCC_0 *)temp_v0)->unk_08 in func_800D5DCC */

typedef struct S_800D5DCC_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D5DCC_9;   /* ((S_800D5DCC_1 *)arg0)->unk_08 in func_800D5DCC */

typedef struct S_800D5DCC_10 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_800D5DCC_10;   /* ((S_800D5DCC_0 *)temp_v0)->unk_0C in func_800D5DCC */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 rand();

extern u8 D_800D5AC0[];
extern u8 D_800D5CA0[];
extern s16 D_800E2468[];

/* Spawn an effect offset from the source with randomized directional velocity. */
void func_800D5DCC(S_800D5DCC_1 *source, s16 angle, s32 effect_value)
{
    S_800D5DCC_2 *pos_x;
    S_800D5DCC_4 *pos_y;
    S_800D5DCC_5 *velocity_x;
    S_800D5DCC_6 *velocity_y;
    S_800D5DCC_3 *direction;
    S_800D5DCC_7 *effect_state;
    void *effect;

    effect = func_8003FD64(0x211, source);
    if (effect != NULL) {
        ((S_800D5DCC_0 *)effect)->unk_10 = D_800D5CA0;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)effect)->unk_08))->unk_02 =
            ((S_800D5DCC_9 *)(source->unk_08))->unk_02;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)effect)->unk_08))->unk_06 =
            ((S_800D5DCC_9 *)(source->unk_08))->unk_06;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)effect)->unk_08))->unk_0A =
            ((S_800D5DCC_9 *)(source->unk_08))->unk_0A - 0x14;
        direction = ((angle >> 7) & 0x1C) + (u8 *)D_800E2468;
        pos_x = ((S_800D5DCC_0 *)effect)->unk_08;
        pos_x->unk_02 += direction->unk_00 * 0x10;
        pos_y = ((S_800D5DCC_0 *)effect)->unk_08;
        pos_y->unk_06 += direction->unk_02 * 0x10;
        ((S_800D5DCC_10 *)(((S_800D5DCC_0 *)effect)->unk_0C))->unk_06 = 6;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)effect)->unk_08))->unk_0C =
            ((rand(pos_y) & 0x7FFF) - 0x4000) << 6;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)effect)->unk_08))->unk_10 =
            ((rand() & 0x7FFF) - 0x4000) << 6;
        ((S_800D5DCC_8 *)(((S_800D5DCC_0 *)effect)->unk_08))->unk_14 =
            ((rand() & 0x7FFF) - 0x4000) << 5;
        velocity_x = ((S_800D5DCC_0 *)effect)->unk_08;
        velocity_x->unk_0C += direction->unk_00 * 0x160000;
        effect_state = (u8 *)effect + 0x20;
        velocity_y = ((S_800D5DCC_0 *)effect)->unk_08;
        velocity_y->unk_10 += direction->unk_02 * 0x160000;
        effect_state->unk_14 = angle;
        effect_state->unk_32 = 7;
        effect_state->unk_34 = 7;
        func_8004491C(effect, D_800D5AC0, velocity_y);
        ((S_800D5DCC_0 *)effect)->unk_20 = effect_value;
        effect_state->unk_08 = effect_value;
    }
}
