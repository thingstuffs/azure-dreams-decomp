#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80165018_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80165018_0;   /* obj in create_jittered_child_effect */

typedef struct S_80165018_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80165018_3;   /* pos in create_jittered_child_effect */

typedef struct S_80165018_4 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x26];
    s16 unk_32;
    s16 unk_34;
} S_80165018_4;   /* tail in create_jittered_child_effect */

   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in create_jittered_child_effect */

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern s32 rand(void);
extern u8 child_particle_draw_address[];
extern u8 D_80164DA4[];

/* Create an effect at a randomized offset from its parent and initialize its state. */
void create_jittered_child_effect(EntityRec *parent, s32 effect_value, s16 effect_size, s16 offset_x, s16 offset_y,
                   s16 offset_z) {
    ObjectNodeHeader *effect;
    SpriteFrameState *state;
    S_80165018_4 *effect_data;
    S_80165018_3 *transform;
    s16 jitter;
    s16 coordinate;

    effect = allocate_list_node(0x211, parent);
    if (effect != 0) {
        effect->update_callback = D_80164DA4;
        jitter = rand() & 7;
        coordinate = ((MovingPosition *)((*(void * *)&parent->z)))->x + offset_x;
        coordinate -= 3;
        coordinate += jitter;
        (effect->position)->x.w.i = (s16)coordinate;
        jitter = rand() & 7;
        coordinate = ((MovingPosition *)((*(void * *)&parent->z)))->y + offset_y;
        coordinate -= 3;
        coordinate += jitter;
        (effect->position)->y.w.i = (s16)coordinate;
        jitter = rand() & 7;
        coordinate = ((MovingPosition *)((*(void * *)&parent->z)))->z + offset_z;
        coordinate -= 3;
        coordinate += jitter;
        (effect->position)->z.w.i = (s16)coordinate;
        effect->sprite->depth_bias = 0;
        state = effect->sprite;
        effect_data = (u8 *)effect + 0x20;
        state->flags = state->flags | 0xC;
        effect->sprite->tpage_abr = 0x20;
        transform = effect->position;
        transform->unk_14 = 0;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        effect_data->unk_32 = effect_size;
        effect_data->unk_34 = effect_size;
        register_node(effect, child_particle_draw_address);
        ((S_80165018_0 *)effect)->unk_20 = effect_value;
        effect_data->unk_08 = effect_value;
    }
}

/* MECHANISM: S3/s4 stack-argument holds reproduce the 0x30 frame and seven-register save set. One
   cached obj+8 pointer collapses the three zero stores to retail's single-load form. */
