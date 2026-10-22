#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

#ifndef NULL
#define NULL 0
#endif

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in create_random_velocity_child_effect */

void *allocate_list_node();
s32 register_node();
s32 rand();
extern u8 D_80164BC4[];
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
void create_random_velocity_child_effect(EntityRec *parent, s32 state_value, s16 pair_value, s16 offset_x, s16 offset_y, s16 offset_z)
{
    S_80164ED0_1 *effect_data;
    ObjectNodeHeader *effect;

    effect = allocate_list_node(0x211, parent);
    if (effect != NULL) {
        effect->unk_10 = D_80164DA4;
        (effect->position)->x.w.i = (s16)
        (((MovingPosition *)((*(void * *)&parent->z)))->unk_02 + offset_x);
        (effect->position)->y.w.i = (s16)
        (((MovingPosition *)((*(void * *)&parent->z)))->unk_06 + offset_y);
        (effect->position)->z.w.i = (s16)
        (((MovingPosition *)((*(void * *)&parent->z)))->unk_0A + offset_z);
        effect->sprite->unk_06 = 6;
        (effect->position)->velocity_x = (s32)
        (((rand() & 0x7FFF) - 0x4000) << 6);
        (effect->position)->velocity_y = (s32)
        (((rand() & 0x7FFF) - 0x4000) << 6);
        effect_data = ((void *)effect) + 0x20;
        (effect->position)->velocity_z = (s32)
        (((rand() & 0x7FFF) - 0x4000) << 6);
        effect_data->unk_32 = pair_value;
        effect_data->unk_34 = pair_value;
        register_node(effect, D_80164BC4);
        ((S_80164ED0_0 *)effect)->unk_20 = state_value;
        effect_data->unk_08 = state_value;
    }
}
