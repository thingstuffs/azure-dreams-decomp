#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"

#ifndef NULL
#define NULL 0
#endif

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in create_random_velocity_child_effect */

#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/effect/particle.h"
extern u8 child_particle_draw_address[];
extern u8 D_80164DA4[];

typedef struct S_80164ED0_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80164ED0_0;

typedef struct S_80164ED0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80164ED0_1;

/* Creates an effect relative to its parent with randomized motion and initial state values. */
void create_random_velocity_child_effect(ObjectNodeHeader *parent, s32 state_value, s16 pair_value, s16 offset_x, s16 offset_y, s16 offset_z)
{
    S_80164ED0_1 *effect_data;
    ObjectNodeHeader *effect;

    effect = allocate_list_node(0x211, &parent->next);
    if (effect != NULL) {
        effect->update_callback = D_80164DA4;
        (effect->position)->x.w.i = (s16)
        ((u16)parent->position->x.w.i + offset_x);
        (effect->position)->y.w.i = (s16)
        ((u16)parent->position->y.w.i + offset_y);
        (effect->position)->z.w.i = (s16)
        ((u16)parent->position->z.w.i + offset_z);
        effect->sprite->depth_bias = 6;
        (effect->position)->velocity_x = (s32)
        (((rand() & 0x7FFF) - 0x4000) << 6);
        (effect->position)->velocity_y = (s32)
        (((rand() & 0x7FFF) - 0x4000) << 6);
        effect_data = ((void *)effect) + 0x20;
        (effect->position)->velocity_z = (s32)
        (((rand() & 0x7FFF) - 0x4000) << 6);
        effect_data->unk_32 = pair_value;
        effect_data->unk_34 = pair_value;
        register_node(effect, child_particle_draw_address);
        ((S_80164ED0_0 *)effect)->unk_20 = state_value;
        effect_data->unk_08 = state_value;
    }
}
