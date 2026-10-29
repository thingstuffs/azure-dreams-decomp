#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "sdk/libc.h"

#ifndef NULL
#define NULL 0
#endif

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in create_short_lived_child_particle */

#include "engine/node/allocation.h"
#include "engine/node.h"
#include "dungeon/effect/particle.h"
extern u8 child_particle_draw_address[];
extern u8 D_801654F0[];

typedef struct S_801656F8_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_801656F8_0;

typedef struct S_801656F8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
} S_801656F8_1;

/* Creates an effect offset from its source with randomized motion. */
void create_short_lived_child_particle(ObjectNodeHeader *source, s16 effect_param, s32 state_value, s16 offset_x, s16 offset_y,
                   s16 offset_z, s32 motion_z)
{
    S_801656F8_1 *effect_state;
    ObjectNodeHeader *effect;

    effect = allocate_list_node(0x211, &source->next);
    if (effect != NULL) {
        effect->update_callback = D_801654F0;
        (effect->position)->x.w.i = (s16)
        ((u16)source->position->x.w.i + offset_x);
        (effect->position)->y.w.i = (s16)
        ((u16)source->position->y.w.i + offset_y);
        (effect->position)->z.w.i = (s16)
        ((u16)source->position->z.w.i + offset_z);
        effect->sprite->depth_bias = 6;
        (effect->position)->velocity_x = (s32)
        (((rand() & 0x7FFF) - 0x4000) << 4);
        (effect->position)->velocity_y = (s32)
        (((rand() & 0x7FFF) - 0x4000) << 4);
        effect_state = ((void *)effect) + 0x20;
        (effect->position)->velocity_z = motion_z;
        effect_state->unk_14 = effect_param;
        effect_state->unk_32 = 8;
        effect_state->unk_34 = 8;
        register_node(effect, child_particle_draw_address);
        ((S_801656F8_0 *)effect)->unk_20 = state_value;
        effect_state->unk_08 = state_value;
    }
}
