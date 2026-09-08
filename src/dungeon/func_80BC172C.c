#include "common.h"
#include "m2c_compat.h"

typedef struct S_80BC172C_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80BC172C_2;   /* held_arg0 in func_80BC172C */

typedef struct S_80BC172C_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80BC172C_3;   /* temp_v0 in func_80BC172C */

typedef struct S_80BC172C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80BC172C_4;   /* ((S_80BC172C_2 *)held_arg0)->unk_08 in func_80BC172C */

typedef struct S_80BC172C_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80BC172C_5;   /* ((S_80BC172C_3 *)temp_v0)->unk_08 in func_80BC172C */

typedef struct S_80BC172C_6 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80BC172C_6;   /* ((S_80BC172C_3 *)temp_v0)->unk_0C in func_80BC172C */




extern u8 D_80170884[];
extern void *func_8003FD64(s32, void *);
extern M2C_UNK func_8004491C(void *, void *);
extern s32 rand(void);
extern M2C_UNK D_80170BFC;

typedef struct S_80BC172C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80BC172C_0;   /* temp_v0 in func_80BC172C */

typedef struct S_80BC172C_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
} S_80BC172C_1;   /* temp_s0 in func_80BC172C */

/* Spawn an effect at an offset from its parent with randomized motion. */
void func_80BC172C(void *parent_arg, register s16 effect_param_arg, register s32 state_value_arg, register s32 unused_arg, register s32 offset_x_arg, register s32 offset_y_arg, register s32 offset_z_arg) {
    register void *parent = parent_arg;
    register s16 effect_param = effect_param_arg;
    register s32 state_value = state_value_arg;
    register s32 offset_x = offset_x_arg;
    register s32 offset_y = offset_y_arg;
    register s32 offset_z = offset_z_arg;
    S_80BC172C_1 *effect_data;
    void *effect;
    u16 parent_x;

    effect = func_8003FD64(0x211, parent);
    if (effect != NULL) {
        ((S_80BC172C_0 *)effect)->unk_10 = &D_80170BFC;
        do {
            parent_x = ((S_80BC172C_4 *)(((S_80BC172C_2 *)parent)->unk_08))->unk_02;
            ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_02 = (s16) (parent_x + offset_x);
            ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_06 = (s16) (((S_80BC172C_4 *)(((S_80BC172C_2 *)parent)->unk_08))->unk_06 + offset_y);
            ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_0A = (s16) ((((S_80BC172C_4 *)(((S_80BC172C_2 *)parent)->unk_08))->unk_0A + offset_z) - 0x64);
        } while (0);
        ((S_80BC172C_6 *)(((S_80BC172C_3 *)effect)->unk_0C))->unk_06 = 6;
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_0C = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_10 = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        effect_data = effect + 0x20;
        ((S_80BC172C_5 *)(((S_80BC172C_3 *)effect)->unk_08))->unk_14 = (s32) (((rand() & 0x7FFF) - 0x4000) << 7);
        effect_data->unk_14 = effect_param;
        effect_data->unk_32 = 5;
        effect_data->unk_34 = 5;
        func_8004491C(effect, D_80170884);
        ((S_80BC172C_0 *)effect)->unk_20 = state_value;
        effect_data->unk_08 = state_value;
    }
}
