#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_moving_views.h"

typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif


extern void select_record_entry_and_value();
extern s32 register_node();
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern M2C_UNK D_80024330[];
extern u8 D_800DEAE0[];

typedef struct S_8185CE28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8185CE28_0;

typedef struct S_8185CE28_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
} S_8185CE28_1;

   /* arg1 in create_expanding_spiral_effect */

typedef struct S_8185CE28_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8185CE28_3;

/* Creates an effect at an indexed radial offset from the supplied position. */
s32 create_expanding_spiral_effect(s32 effect_param, MovingPosition *position, s16 effect_index)
{
    s16 phase_index;
    s32 phase_step;
    S_8185CE28_3 *component;
    S_8185CE28_1 *state;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        phase_step = effect_index * 3;
        ((S_8185CE28_0 *)effect)->unk_20 = effect_param;
        state = ((void *)effect) + 0x20;
        effect->unk_10 = D_80024330;
        phase_index = phase_step % 8;
        state->unk_1C = phase_index << 9;
        state->unk_20 = 0x20;
        state->unk_1E = 0;
        state->unk_22 = -8;
        state->unk_24 = phase_index;
        state->unk_06 = position->unk_02;
        state->unk_0A = position->unk_06;
        state->unk_0E = position->unk_0A;
        component = effect->sprite;
        component->unk_0E = 0x80;
        component->unk_0D = 0x80;
        component->unk_0C = 0x80;
        select_record_entry_and_value(component, D_800DEAE0, 0);
        component->unk_1E = 0x1800;
        component->unk_1C = 0x1800;
        component->unk_12 = 0x7E0B;
        component->unk_14 |= 0xC;
        component->unk_10 |= 0x20;
        component->unk_14 |= 0x100;
        register_node(effect, project_sprite_chain);
        component = effect->position;
        component->unk_02 = state->unk_06 +
            ((func_800644B8(state->unk_1C) >> 4) *
             state->unk_20 >> 8);
        component->unk_06 = state->unk_0A +
            ((func_80064584(state->unk_1C) >> 4) *
             state->unk_20 >> 8);
        component->unk_0A = state->unk_0E - 8;
        return (s32) effect;
    }
    return 0;
}
