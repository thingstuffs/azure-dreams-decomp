#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/dungeon_moving_views.h"



typedef struct S_800DB2DC_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800DB2DC_6;





extern void *func_8003FD64();
struct D_800DB420_Obj;
struct D_800DB420_RngOut;
struct D_800DB420_Effect;
extern void advance_jittered_effect_modes(struct D_800DB420_Obj *state, struct D_800DB420_RngOut *position, struct D_800DB420_Effect *effect);

typedef struct S_800DB2DC_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x26];
    u16 unk_4A;
} S_800DB2DC_0;

typedef struct S_800DB2DC_1 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800DB2DC_1;   /* held_arg2 in create_two_effect_groups */

typedef struct S_800DB2DC_2 {
    u8 pad_00[0x12];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x12];
    s32 unk_28;
    s32 unk_2C;
} S_800DB2DC_2;   /* held_arg1 in create_two_effect_groups */

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
} S_800DB2DC_3;

   /* held_arg0 in create_two_effect_groups */

typedef struct S_800DB2DC_5 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_800DB2DC_5;

/* Creates two groups of four effects using the source position and visual state. */
void create_two_effect_groups(MovingPosition *position, S_800DB2DC_2 *source_visual, S_800DB2DC_1 *source_arg, s16 effect_param) {
    register M2C_UNK *callback;
    s32 scale;
    s16 saved_param;
    s32 effects_left;
    s32 group_step;
    u16 visual_flags;
    u16 source_offset;
    s32 visual_word;
    S_800DB2DC_3 *visual;
    S_800DB2DC_5 *effect_state;
    void *effect;

    saved_param = effect_param;
    group_step = 3;
    callback = advance_jittered_effect_modes;
    scale = 0x1000;
    do {
        effects_left = 3;
        do {
            effect = func_8003FD64(0x312, ((M2C_UNK *)&D_80083498.next));
            if (effect != 0) {
                ((S_800DB2DC_0 *)effect)->unk_10 = callback;
                visual = ((S_800DB2DC_0 *)effect)->unk_0C;
                ((S_800DB2DC_0 *)effect)->unk_4A =
                    (u16)source_arg->unk_2A;
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
                ((MovingPosition *)(((S_800DB2DC_6 *)effect)->unk_08))->unk_02 =
                    (u16)position->unk_02;
                ((MovingPosition *)(((S_800DB2DC_6 *)effect)->unk_08))->unk_06 =
                    (u16)position->unk_06;
                ((MovingPosition *)(((S_800DB2DC_6 *)effect)->unk_08))->unk_0A =
                    (u16)position->unk_0A;
                effect_state = effect + 0x20;
                effect_state->unk_06 = saved_param;
                effect_state->unk_04 = (s16)(group_step != 0);
                visual->unk_2C =
                    (s32)source_visual->unk_2C;
            }
        } while (--effects_left >= 0);
        group_step -= 3;
    } while (group_step >= 0);
}
