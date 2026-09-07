#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800DB2DC_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800DB2DC_6;   /* var_a2 in func_800DB2DC */

typedef struct S_800DB2DC_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800DB2DC_7;   /* ((S_800DB2DC_6 *)var_a2)->unk_08 in func_800DB2DC */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FD64();
extern M2C_UNK D_80083498;
extern M2C_UNK D_800DB420;

typedef struct S_800DB2DC_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x26];
    u16 unk_4A;
} S_800DB2DC_0;   /* var_a2 in func_800DB2DC */

typedef struct S_800DB2DC_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800DB2DC_1;   /* held_arg2 in func_800DB2DC */

typedef struct S_800DB2DC_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    s32 unk_28;
    s32 unk_2C;
} S_800DB2DC_2;   /* held_arg1 in func_800DB2DC */

typedef struct S_800DB2DC_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
    s32 unk_2C;
} S_800DB2DC_3;   /* temp_a0 in func_800DB2DC */

typedef struct S_800DB2DC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800DB2DC_4;   /* held_arg0 in func_800DB2DC */

typedef struct S_800DB2DC_5 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_800DB2DC_5;   /* temp_v1 in func_800DB2DC */

/* Creates two groups of four effects using the source position and visual state. */
void func_800DB2DC(void *position_arg, void *visual_arg, void *source_arg, s16 effect_param) {
    register M2C_UNK *callback;
    s32 scale;
    S_800DB2DC_4 *position;
    S_800DB2DC_2 *source_visual;
    register S_800DB2DC_1 *source_object ASM_REG("$23");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 saved_param;
    s32 effects_left;
    register s32 group_step ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u16 visual_flags;
    u16 source_offset;
    s32 visual_word;
    S_800DB2DC_3 *visual;
    S_800DB2DC_5 *effect_state;
    void *effect;

    effect = source_arg;
    position = position_arg;
    source_visual = visual_arg;
    source_object = source_arg;
    saved_param = effect_param;
    group_step = 3;
    callback = &D_800DB420;
    scale = 0x1000;
    do {
        effects_left = 3;
        do {
            effect = func_8003FD64(0x312, &D_80083498, effect);
            if (effect != 0) {
                ((S_800DB2DC_0 *)effect)->unk_10 = callback;
                visual = ((S_800DB2DC_0 *)effect)->unk_0C;
                ((S_800DB2DC_0 *)effect)->unk_4A =
                    (u16)source_object->unk_2A;
                visual_word = source_visual->unk_28;
                visual->unk_1E = scale;
                visual->unk_1C = scale;
                visual->unk_28 = visual_word;
                visual_flags = source_visual->unk_14;
                visual->unk_14 = visual_flags;
                source_offset = source_visual->unk_12;
                visual->unk_0C = 0x808080;
                visual->unk_14 = (u16)(visual_flags | 0xC);
                visual->unk_12 =
                    (s16)(source_offset - 0x80);
                ((S_800DB2DC_0 *)effect)->unk_20 = position;
                ((S_800DB2DC_7 *)(((S_800DB2DC_6 *)effect)->unk_08))->unk_02 =
                    (u16)position->unk_02;
                ((S_800DB2DC_7 *)(((S_800DB2DC_6 *)effect)->unk_08))->unk_06 =
                    (u16)position->unk_06;
                ((S_800DB2DC_7 *)(((S_800DB2DC_6 *)effect)->unk_08))->unk_0A =
                    (u16)position->unk_0A;
                effect_state = effect + 0x20;
                effect_state->unk_06 = saved_param;
                effect_state->unk_04 = (s16)(group_step != 0);
                visual->unk_2C =
                    (s32)source_visual->unk_2C;
            }
            ASM_KEEP(effects_left);   /* MATCH pin: keeps a constant in a register as retail does */
        } while (--effects_left >= 0);
        group_step -= 3;
    } while (group_step >= 0);
    ASM_KEEP(position);   /* MATCH pin: load-bearing for the whole function shape */
}
