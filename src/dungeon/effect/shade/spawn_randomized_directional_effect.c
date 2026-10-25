#include "common.h"
#include "dungeon/effect/shade.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

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
} S_800D5DCC_0;

typedef struct S_800D5DCC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800D5DCC_2;

typedef struct S_800D5DCC_3 {
    s16 unk_00;
    s16 unk_02;
} S_800D5DCC_3;

typedef struct S_800D5DCC_4 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_800D5DCC_4;

typedef struct S_800D5DCC_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800D5DCC_5;

typedef struct S_800D5DCC_6 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800D5DCC_6;

typedef struct S_800D5DCC_7 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
} S_800D5DCC_7;

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in spawn_randomized_directional_effect */

extern void *allocate_list_node();
extern void register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 rand();

extern u8 D_800D5AC0[];

extern s16 actor_direction_step_pairs[];

/* Spawn an effect offset from the source with randomized directional velocity. */
void spawn_randomized_directional_effect(EntityRec *source, s16 angle, s32 effect_value)
{
    ObjectPosition *pos_x;
    ObjectPosition *pos_y;
    ObjectPosition *velocity_x;
    ObjectPosition *velocity_y;
    S_800D5DCC_3 *direction;
    S_800D5DCC_7 *effect_state;
    ObjectNodeHeader *effect;

    effect = allocate_list_node(0x211, source);
    if (effect != NULL) {
        effect->update_callback = advance_damped_effect_and_expire;
        (effect->position)->x.w.i =
            ((MovingPosition *)((*(void * *)&source->z)))->x;
        (effect->position)->y.w.i =
            ((MovingPosition *)((*(void * *)&source->z)))->y;
        (effect->position)->z.w.i =
            ((MovingPosition *)((*(void * *)&source->z)))->z - 0x14;
        direction = ((angle >> 7) & 0x1C) + (u8 *)actor_direction_step_pairs;
        pos_x = effect->position;
        pos_x->x.w.i = (u16)pos_x->x.w.i + (direction->unk_00 * 0x10);
        pos_y = effect->position;
        pos_y->y.w.i = (u16)pos_y->y.w.i + (direction->unk_02 * 0x10);
        effect->sprite->depth_bias = 6;
        (effect->position)->velocity_x =
            ((rand() & 0x7FFF) - 0x4000) << 6;
        (effect->position)->velocity_y =
            ((rand() & 0x7FFF) - 0x4000) << 6;
        (effect->position)->velocity_z =
            ((rand() & 0x7FFF) - 0x4000) << 5;
        velocity_x = effect->position;
        velocity_x->velocity_x += direction->unk_00 * 0x160000;
        effect_state = (u8 *)effect + 0x20;
        velocity_y = effect->position;
        velocity_y->velocity_y += direction->unk_02 * 0x160000;
        effect_state->unk_14 = angle;
        effect_state->unk_32 = 7;
        effect_state->unk_34 = 7;
        register_node(effect, D_800D5AC0);
        ((S_800D5DCC_0 *)effect)->unk_20 = effect_value;
        effect_state->unk_08 = effect_value;
    }
}
